"""Verify the supported Black Mesa DLLs and hook instructions without modifying them."""
import argparse
import hashlib
import json
import re
import struct
from pathlib import Path


def read_rva(data, rva, count):
    pe = struct.unpack_from('<I', data, 0x3C)[0]
    if data[pe:pe + 4] != b'PE\0\0':
        raise ValueError('Invalid PE signature')
    sections = struct.unpack_from('<H', data, pe + 6)[0]
    optional_size = struct.unpack_from('<H', data, pe + 20)[0]
    table = pe + 24 + optional_size
    for index in range(sections):
        section = table + index * 40
        virtual_size, virtual_address, raw_size, raw_offset = struct.unpack_from('<IIII', data, section + 8)
        if virtual_address <= rva < virtual_address + max(virtual_size, raw_size):
            offset = rva - virtual_address
            if offset + count > raw_size:
                raise ValueError('Instruction extends beyond section data')
            return data[raw_offset + offset:raw_offset + offset + count]
    raise ValueError(f'RVA {rva:#x} not found in PE sections')


def verify(game):
    source_dir = Path(__file__).resolve().parents[2] / 'src/mods/blackmesa/game'
    source = (source_dir / 'compatibility.cpp').read_text()
    fingerprints = re.findall(r'\{"([^"]+\.dll)", "([0-9a-f]{64})"\}', source)
    if len(fingerprints) != 8:
        raise ValueError('Expected eight module fingerprints')
    images, modules, checks = {}, [], []
    for name, expected in fingerprints:
        relative = Path('bms/bin' if name == 'client.dll' else 'bin') / name
        data = (game / relative).read_bytes()
        actual = hashlib.sha256(data).hexdigest()
        modules.append({'file': relative.as_posix(), 'matches': actual == expected, 'sha256': actual})
        images[name] = data
    bases = {'CLIENT_BASE': 'client.dll', 'ENGINE_BASE': 'engine.dll', 'RENDERER_BASE': 'shaderapidx9.dll',
             'STDSHADERDX9_BASE': 'stdshader_dx9.dll', 'STUDIORENDER_BASE': 'studiorender.dll'}
    guard_source = (source_dir / 'build19042901_checks.inc').read_text()
    pattern = r'expect_bytes\((\w+) \+ (0x[0-9A-F]+), "([^"]+)", "([^"]+)", (\d+)\)'
    for base, offset, label, literals, count in re.findall(pattern, guard_source):
        expected = bytes(int(value, 16) for value in re.findall(r'\\x([0-9A-Fa-f]{2})', literals))
        count = int(count)
        if len(expected) != count:
            raise ValueError(f'Invalid expected length: {label}')
        actual = read_rva(images[bases[base]], int(offset, 16), count)
        checks.append({'site': label, 'matches': actual == expected})
    if len(checks) != 27:
        raise ValueError('Expected 26 hook sites plus the flashlight field check')
    return {'supported_steam_build': 19042901, 'passed': all(x['matches'] for x in modules + checks),
            'modules': modules, 'instruction_checks': checks}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('game_directory', type=Path, help='Folder containing bms.exe')
    parser.add_argument('--json', type=Path, help='Optional destination for the verification report')
    args = parser.parse_args()
    try:
        result = verify(args.game_directory)
    except (OSError, ValueError, struct.error) as error:
        parser.exit(1, f'Verification failed: {error}\n')
    if args.json:
        args.json.write_text(json.dumps(result, indent=2), encoding='utf-8')
    print('PASS' if result['passed'] else 'FAIL', '- 8 module fingerprints and 27 instruction checks')
    for entry in result['modules'] + result['instruction_checks']:
        if not entry['matches']:
            print('Mismatch:', entry.get('file', entry.get('site')))
    raise SystemExit(0 if result['passed'] else 1)


if __name__ == '__main__':
    main()
