// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "runtime_managed_registration_access.h"

typedef struct RuntimePoolCell28 { unsigned char opaque[28]; } RuntimePoolCell28;
typedef char RuntimePoolCellStride28[sizeof(RuntimePoolCell28) == 28 ? 1 : -1];
extern int D_0036AE40, D_0036AE44;
extern unsigned char D_004D2CA0[], D_004D2CE0[];

void func_002B4458(struct S *storage, unsigned int *group, unsigned int *index)
{
    RuntimePoolCell28 *cell = (RuntimePoolCell28 *)storage;
    unsigned int block;
    for (block = 0; block < (unsigned int)D_0036AE40; ++block) {
        RuntimePoolCell28 *base = ((RuntimePoolCell28 **)D_004D2CA0)[block];
        if ((unsigned int)cell >= (unsigned int)base && (unsigned int)cell < (unsigned int)(base + 1024)) {
            *group = block;
            *index = cell - base;
            return;
        }
    }
    if ((unsigned int)D_0036AE40 < 16) {
        for (block = 0; block < (unsigned int)D_0036AE44; ++block) {
            RuntimePoolCell28 *base = ((RuntimePoolCell28 **)D_004D2CE0)[block];
            if ((unsigned int)cell >= (unsigned int)base && (unsigned int)cell < (unsigned int)(base + 1024)) {
                *group = D_0036AE40;
                *index = cell - base;
                ((RuntimePoolCell28 **)D_004D2CA0)[D_0036AE40++] = base;
                return;
            }
        }
    }
    *group = 0;
    *index = 0;
}
