// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "runtime_managed_registration_access.h"

typedef struct RuntimePoolCell24 { unsigned char opaque[24]; } RuntimePoolCell24;
typedef char RuntimePoolCellStride24[sizeof(RuntimePoolCell24) == 24 ? 1 : -1];
extern int D_0036AE68, D_0036AE6C;
extern unsigned char D_004D2E50[], D_004D2E90[];

void func_002B4BD8(struct S *storage, unsigned int *group, unsigned int *index)
{
    RuntimePoolCell24 *cell = (RuntimePoolCell24 *)storage;
    unsigned int block;
    for (block = 0; block < (unsigned int)D_0036AE68; ++block) {
        RuntimePoolCell24 *base = ((RuntimePoolCell24 **)D_004D2E50)[block];
        if ((unsigned int)cell >= (unsigned int)base && (unsigned int)cell < (unsigned int)(base + 256)) {
            *group = block;
            *index = cell - base;
            return;
        }
    }
    if ((unsigned int)D_0036AE68 < 16) {
        for (block = 0; block < (unsigned int)D_0036AE6C; ++block) {
            RuntimePoolCell24 *base = ((RuntimePoolCell24 **)D_004D2E90)[block];
            if ((unsigned int)cell >= (unsigned int)base && (unsigned int)cell < (unsigned int)(base + 256)) {
                *group = D_0036AE68;
                *index = cell - base;
                ((RuntimePoolCell24 **)D_004D2E50)[D_0036AE68++] = base;
                return;
            }
        }
    }
    *group = 0;
    *index = 0;
}
