0. This fork supports Windows Steam public build 19042901. Use the normal public branch, not black-mesa-1-0 or public-beta. The plugin rejects different DLL fingerprints; see docs/blackmesa-build19042901.txt in the repository.
1. Install an x86 RTX Remix runtime. This port was tested with e2f8119-845 from the original Black Mesa release bundle: https://github.com/xoxor4d/remix-comp-projects/releases/tag/1.0-BlackMesa . Newer runtimes require separate validation.
2. Drag remix files into "steamapps/common/Black Mesa/bin"
3. [Download UltimateAsiLoader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases) OR copy "_general/UltimateAsiLoader.dll" to "steamapps/common/Black Mesa/bin" folder and rename it to "winmm.dll"
4. Copy all files within "assets/blackmesa" to "steamapps/common/Black Mesa" (next to "bms.exe")
5. Copy the rebuilt a_blackmesa-rtx.asi to "steamapps/common/Black Mesa/bin", replacing the older plugin after backing it up. Do not replace the game's original DLLs.
6. Install the separate author's lighting/content pack from https://www.moddb.com/mods/black-mesa-remixed-poc-inbound/downloads/black-mesa-inbound-ride-and-lab-rtx-remix-mod. Its coverage is limited to the opening campaign; the compatibility plugin alone does not supply lighting for the whole game.
7. Launch with run-bms-rtx-windowed.bat for 1280x720 windowed play. run-bms-rtx-computer-use.bat additionally enables missing-scan-code repair and disables raw mouse input for desktop automation. Both launchers must be beside bms.exe. The original run-bms-rtx.bat remains available for custom arguments.
