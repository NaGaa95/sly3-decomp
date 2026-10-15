// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" unsigned char *g_pbGlobalBase;
extern "C" unsigned char *g_pbGlobal;
extern "C" unsigned char *g_pbSlot;
extern "C" unsigned char *g_pbSlotBase;
extern "C" int g_cStack;
extern "C" char g_stackGuard[12];
extern "C" void func_00271B80(void *p);
extern "C" char D_004F3000;
extern "C" int D_004D3000;

extern "C" int func_001D23E0(int unused_request)
{
    return g_pbSlot - g_pbGlobal;
}

extern "C" void func_001D23F8()
{
    unsigned char *pb = (unsigned char *)(((int)&D_004F3000 + 15) & ~15);
    unsigned char *pbEnd = (unsigned char *)0x02000000;
    g_pbGlobalBase = g_pbGlobal = pb;
    g_pbSlot = g_pbSlotBase = pbEnd;
    g_cStack = -1;
    func_00271B80(g_stackGuard);
    D_004D3000 = 0x1234ABCD;
}
