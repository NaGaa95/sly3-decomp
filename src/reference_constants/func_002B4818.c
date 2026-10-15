// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "runtime_managed_registration_access.h"

typedef struct RuntimePoolCell12 { unsigned char opaque[12]; } RuntimePoolCell12;
typedef char RuntimePoolCellStride12[sizeof(RuntimePoolCell12) == 12 ? 1 : -1];
extern int D_0036AE54, D_0036AE58;
extern unsigned char D_004D2D78[], D_004D2DB8[];

void func_002B4818(struct S *storage, unsigned int *group, unsigned int *index)
{
    RuntimePoolCell12 *cell = (RuntimePoolCell12 *)storage;
    unsigned int block;
    for (block = 0; block < (unsigned int)D_0036AE54; ++block) {
        RuntimePoolCell12 *base = ((RuntimePoolCell12 **)D_004D2D78)[block];
        if ((unsigned int)cell >= (unsigned int)base && (unsigned int)cell < (unsigned int)(base + 256)) {
            *group = block;
            *index = cell - base;
            return;
        }
    }
    if ((unsigned int)D_0036AE54 < 16) {
        for (block = 0; block < (unsigned int)D_0036AE58; ++block) {
            RuntimePoolCell12 *base = ((RuntimePoolCell12 **)D_004D2DB8)[block];
            if ((unsigned int)cell >= (unsigned int)base && (unsigned int)cell < (unsigned int)(base + 256)) {
                *group = D_0036AE54;
                *index = cell - base;
                ((RuntimePoolCell12 **)D_004D2D78)[D_0036AE54++] = base;
                return;
            }
        }
    }
    *group = 0;
    *index = 0;
}
