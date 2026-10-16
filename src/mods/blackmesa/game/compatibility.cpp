#include "std_include.hpp"
#include <wincrypt.h>
#pragma comment(lib, "advapi32.lib")

namespace mods::blackmesa::game
{
	void compatibility_log(const std::string& message)
	{
		static std::mutex log_mutex;
		const std::lock_guard lock(log_mutex);
		std::cout << "[COMPAT] " << message << std::endl;
		const auto directory = std::filesystem::path(shared::globals::root_path) / "rtx_comp" / "logs";
		std::error_code error;
		std::filesystem::create_directories(directory, error);
		std::ofstream log(directory / "compatibility.log", std::ios::app);
		log << GetTickCount64() << " " << message << '\n';
	}

	static std::string module_sha256(HMODULE module)
	{
		wchar_t path[MAX_PATH]{};
		if (!GetModuleFileNameW(module, path, MAX_PATH)) return {};
		const auto file = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE,
			nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (file == INVALID_HANDLE_VALUE) return {};
		HCRYPTPROV provider = 0;
		HCRYPTHASH hash = 0;
		bool ok = CryptAcquireContextW(&provider, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)
			&& CryptCreateHash(provider, CALG_SHA_256, 0, 0, &hash);
		BYTE buffer[65536];
		while (ok)
		{
			DWORD count = 0;
			if (!ReadFile(file, buffer, sizeof(buffer), &count, nullptr)) { ok = false; break; }
			if (!count) break;
			ok = CryptHashData(hash, buffer, count, 0) != FALSE;
		}
		BYTE digest[32]{};
		DWORD size = sizeof(digest);
		ok = ok && CryptGetHashParam(hash, HP_HASHVAL, digest, &size, 0);
		if (hash) CryptDestroyHash(hash);
		if (provider) CryptReleaseContext(provider, 0);
		CloseHandle(file);
		if (!ok) return {};
		std::string result;
		constexpr char hex[] = "0123456789abcdef";
		for (const auto byte : digest) { result += hex[byte >> 4]; result += hex[byte & 15]; }
		return result;
	}

	static bool expect_bytes(DWORD address, const char* label, const char* expected, size_t count)
	{
		if (memcmp(reinterpret_cast<const void*>(address), expected, count) == 0) return true;
		compatibility_log(std::string("Hook instruction mismatch: ") + label);
		return false;
	}

	bool validate_supported_build()
	{
		struct module_fingerprint { const char* name; const char* hash; };
		constexpr module_fingerprint modules[] = {
			{"engine.dll", "27b041995b308810150b69c643637b27834f146f88abafba3211b70ecfe72dc7"},
			{"client.dll", "d7eb73753306d0148be3b41e0490eaf989e3882d4a113e27e41dbaa0797b36df"},
			{"shaderapidx9.dll", "d277c08127b4d741edbd4289b0c7102676d838809390092c92cca1533b4fae21"},
			{"studiorender.dll", "43385486d356c15713ca48e27b69fe6bf400c8b0f1087921eb6cc3abe1fa7488"},
			{"stdshader_dx9.dll", "6860f0115402843c9bd42de5f77a81e11aca30679706a013e1aa44aa9c4815f8"},
			{"vstdlib.dll", "0fed6cc014670085594edabdc3ce1379317897c7acdc72136b52835c8886dfac"},
			{"materialsystem.dll", "73f7e5e43bd53756e59b08519cbc9cee73efc7deefb33aa1d894018c56d19403"},
			{"vguimatsurface.dll", "7fd91eda04da78d64a520e95d8bd08cc44c2730ef4e1a5ddd33e15c0cc4b9d18"}
		};
		compatibility_log("Checking Black Mesa Steam build 19042901.");
		for (const auto& entry : modules)
		{
			const auto module = GetModuleHandleA(entry.name);
			const auto hash = module ? module_sha256(module) : std::string{};
			if (hash != entry.hash)
			{
				compatibility_log(std::string("Module mismatch: ") + entry.name + " SHA256=" + hash);
				return false;
			}
		}
#include "build19042901_checks.inc"
		compatibility_log("Module fingerprints, all 26 hook sites, and the flashlight field verified.");
		return true;
	}
}
