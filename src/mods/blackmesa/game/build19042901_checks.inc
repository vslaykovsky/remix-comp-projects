// Steam build 19042901; generated from the user-owned Windows depot.
// Client flashlight-off routine: cmp byte ptr [ecx + 0x13D5], 0.
if (!expect_bytes(CLIENT_BASE + 0xBC680, "CLIENT_BASE+BC680 flashlight field", "\x80\xB9\xD5\x13\x00\x00\x00", 7)) return false;
if (!expect_bytes(CLIENT_BASE + 0xCEEF0, "CLIENT_BASE+CEEF0", "\x74\xEE", 2)) return false;
if (!expect_bytes(CLIENT_BASE + 0xE3B28, "CLIENT_BASE+E3B28", "\x75\x2A", 2)) return false;
if (!expect_bytes(CLIENT_BASE + 0xE3B46, "CLIENT_BASE+E3B46", "\x77\x07", 2)) return false;
if (!expect_bytes(CLIENT_BASE + 0x10C7FF, "CLIENT_BASE+10C7FF", "\x0F\x84\x0F\x01\x00\x00", 6)) return false;
if (!expect_bytes(CLIENT_BASE + 0x208559, "CLIENT_BASE+208559", "\x8D\x85\x54\xFE\xFF\xFF", 6)) return false;
if (!expect_bytes(CLIENT_BASE + 0x2091A2, "CLIENT_BASE+2091A2", "\x89\x45\xF8\x8B\x06", 5)) return false;
if (!expect_bytes(CLIENT_BASE + 0x20F0F3, "CLIENT_BASE+20F0F3", "\x68\xA0\x09\x00\x00", 5)) return false;
if (!expect_bytes(CLIENT_BASE + 0x21055D, "CLIENT_BASE+21055D", "\x74\x09", 2)) return false;
if (!expect_bytes(CLIENT_BASE + 0x210565, "CLIENT_BASE+210565", "\x30", 1)) return false;
if (!expect_bytes(ENGINE_BASE + 0xEDDDB, "ENGINE_BASE+EDDDB", "\x75\xD3", 2)) return false;
if (!expect_bytes(ENGINE_BASE + 0x107BD5, "ENGINE_BASE+107BD5", "\x51\xFF\x70\x50\x57", 5)) return false;
if (!expect_bytes(ENGINE_BASE + 0x1082A8, "ENGINE_BASE+1082A8", "\x77\x08", 2)) return false;
if (!expect_bytes(ENGINE_BASE + 0x108ACD, "ENGINE_BASE+108ACD", "\x7C", 1)) return false;
if (!expect_bytes(ENGINE_BASE + 0x108AE3, "ENGINE_BASE+108AE3", "\xE8\x68\xF9\x02\x00", 5)) return false;
if (!expect_bytes(ENGINE_BASE + 0x108BC1, "ENGINE_BASE+108BC1", "\x74\x1E", 2)) return false;
if (!expect_bytes(ENGINE_BASE + 0x108BCA, "ENGINE_BASE+108BCA", "\x75", 1)) return false;
if (!expect_bytes(ENGINE_BASE + 0x10DA10, "ENGINE_BASE+10DA10", "\x74\x14", 2)) return false;
if (!expect_bytes(ENGINE_BASE + 0x10DA2C, "ENGINE_BASE+10DA2C", "\x74\x14", 2)) return false;
if (!expect_bytes(ENGINE_BASE + 0x1255D4, "ENGINE_BASE+1255D4", "\x8D\x83\x60\x01\x00\x00", 6)) return false;
if (!expect_bytes(ENGINE_BASE + 0x1BB328, "ENGINE_BASE+1BB328", "\x68\x03\x01\x00\x00", 5)) return false;
if (!expect_bytes(ENGINE_BASE + 0x1CC8B1, "ENGINE_BASE+1CC8B1", "\xBA\x05\x00\x00\x00", 5)) return false;
if (!expect_bytes(RENDERER_BASE + 0x3C6D7, "RENDERER_BASE+3C6D7", "\x8B\x47\x40\x85\xC0", 5)) return false;
if (!expect_bytes(RENDERER_BASE + 0x3C808, "RENDERER_BASE+3C808", "\x8B\x08\xFF\x77\x50\xFF\x77\x44\x50\xFF\x91\x48\x01\x00\x00", 15)) return false;
if (!expect_bytes(STDSHADERDX9_BASE + 0x7E1BE, "STDSHADERDX9_BASE+7E1BE", "\x7C\x17", 2)) return false;
if (!expect_bytes(STDSHADERDX9_BASE + 0x96945, "STDSHADERDX9_BASE+96945", "\x85\xC0\x0F\x45\xCA", 5)) return false;
if (!expect_bytes(STUDIORENDER_BASE + 0x10BB0, "STUDIORENDER_BASE+10BB0", "\x8B\x47\x04\xF6\x40\x24\x02\x0F\x85\x96\x01\x00\x00", 13)) return false;
