// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/gifs.h"
#include "ee_vu_upload_api.h"

extern unsigned char D_0036E670[];
extern long D_0036DC10[5];
extern unsigned int *D_0036BD40;

extern "C" void func_00271BB8(void *section);
extern "C" void func_00271C10(void *section);
extern "C" int func_0029F5E8(int mode, int unusedTimeout);

extern "C" void func_00196890(QW *chain)
{
    func_00271BB8(D_0036E670);
    for (int i = 0; i < 2; ++i) {
        GIFS builder;
        QW state[64];

        builder.AllocStatic(64, state);
        builder.AddDmaCnt();
        builder.AddPrimPack(0, 1, 0xE);
        builder.PackAD(0x4C, D_0036DC10[i]);
        builder.PackAD(0x4E, D_0036DC10[2]);
        builder.PackAD(0x18, D_0036DC10[3]);
        builder.PackAD(0x40, D_0036DC10[4]);
        builder.PackAD(0x1A, 1);
        builder.PackAD(0x46, 1);
        builder.PackAD(0x45, 0);
        builder.PackAD(0x47, 0x50000);
        builder.EndPrim(1);
        builder.AddDmaEnd();
        func_00293920(0);
        func_0029FD20(D_0036BD40, state);
        func_0029FD20(D_0036BD40, chain);
        func_0029F5E8(0, 0);
    }
    func_00271C10(D_0036E670);
}
