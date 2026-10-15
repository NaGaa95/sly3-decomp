// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "runtime_managed_pool_extensions.h"

typedef struct RuntimePoolCell16 { unsigned char opaque[16]; } RuntimePoolCell16;
typedef char RuntimePoolCellStride16[sizeof(RuntimePoolCell16) == 16 ? 1 : -1];
extern int D_0036AE04, D_0036AE08;
extern unsigned char D_004D2A18[], D_004D2A58[];

void func_002B3930(struct S *storage, unsigned int *group, unsigned int *index)
{
    RuntimePoolCell16 *cell = (RuntimePoolCell16 *)storage;
    unsigned int block;
    for (block = 0; block < (unsigned int)D_0036AE04; ++block) {
        RuntimePoolCell16 *base = ((RuntimePoolCell16 **)D_004D2A18)[block];
        if ((unsigned int)cell >= (unsigned int)base && (unsigned int)cell < (unsigned int)(base + 2048)) {
            *group = block;
            *index = cell - base;
            return;
        }
    }
    if ((unsigned int)D_0036AE04 < 16) {
        for (block = 0; block < (unsigned int)D_0036AE08; ++block) {
            RuntimePoolCell16 *base = ((RuntimePoolCell16 **)D_004D2A58)[block];
            if ((unsigned int)cell >= (unsigned int)base && (unsigned int)cell < (unsigned int)(base + 2048)) {
                *group = D_0036AE04;
                *index = cell - base;
                ((RuntimePoolCell16 **)D_004D2A18)[D_0036AE04++] = base;
                return;
            }
        }
    }
    *group = 0;
    *index = 0;
}
