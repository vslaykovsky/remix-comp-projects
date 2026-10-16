@echo off
setlocal
cd /d "%~dp0"
if not exist "bms.exe" (
  echo Copy this launcher to the Black Mesa folder beside bms.exe.
  pause
  exit /b 1
)
start "" bms.exe -insecure -steam -novid -dx9 -dxlevel 95 -oldgameui -force_vendor_id 0x10DE -force_device_id 0x1180 -disable_d3d9_hacks -limitvsconst -softparticlesdefaultoff -disallowhwmorph -no_compressed_verts -nogamepadui -nobeep -windowed -w 1280 -h 720 -condebug -rtx-computer-use +m_rawinput 0 +mat_phong 1
