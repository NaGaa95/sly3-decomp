// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/dmas.h"

extern int D_0036DCAC;
extern QW D_0036DCB0[];
extern "C" void func_00196890(QW *chain);

extern "C" void func_00196A10(void)
{
    DMAS builder;
    QW chain[2];

    builder.AllocStatic(2, chain);
    builder.AddDmaRefs(D_0036DCAC, D_0036DCB0);
    builder.AddDmaEnd();
    func_00196890(chain);
}
