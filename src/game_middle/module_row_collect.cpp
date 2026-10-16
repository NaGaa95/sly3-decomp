// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/heap.h"

struct CollectedRow {
    unsigned char prefix[0x18];
    unsigned long flags;
    unsigned char rest[0xD0 - 0x20];
};
struct RowModule {
    unsigned char prefix[0x20];
    RowModule *next;
    unsigned char rest[0xD0 - 0x24];
    int count;
    CollectedRow *rows;
};
extern "C" RowModule *D_004786E0;
extern "C" void *func_001D25B0(ALLOCREQ *);

extern "C" void func_001DC7E0(int *count, CollectedRow ***values)
{
    RowModule *module;
    unsigned int capacity = 0;
    for (module = D_004786E0; module; module = module->next)
        capacity += module->count;
    ALLOCREQ request;
    request.cb = capacity * sizeof(CollectedRow *);
    request.cbAlign = 16;
    CollectedRow **allocated = (CollectedRow **)func_001D25B0(&request);
    CollectedRow **next = allocated;
    for (module = D_004786E0; module; module = module->next) {
        for (int index = 0; index < module->count; ++index) {
            CollectedRow *row = module->rows + index;
            if (!(row->flags & 0x10000))
                *next++ = row;
        }
    }
    *count = next - allocated;
    *values = allocated;
}

typedef char CollectedRowFlagWidth[(sizeof(unsigned long) == 8) ? 1 : -1];
typedef char CollectedRowStride[(sizeof(CollectedRow) == 0xD0) ? 1 : -1];
typedef char RowModuleCountOffset[((unsigned int)&((RowModule *)0)->count == 0xD0) ? 1 : -1];
typedef char RowModuleRowsOffset[((unsigned int)&((RowModule *)0)->rows == 0xD4) ? 1 : -1];
