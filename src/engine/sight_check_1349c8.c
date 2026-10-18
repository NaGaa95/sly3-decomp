// SLY3_CFLAGS: -Os -G0
#include "heap_frame_api.h"
typedef int Qword __attribute__((mode(TI)));
struct SightEntry { short delta, padding; char *(*fn)(void *); };
struct SightTarget { unsigned char prefix[0xC]; struct SightEntry *table; };
struct SightOwner {
    unsigned char prefix[0xDC];
    void *context;
    unsigned char gapE0[0x10D0 - 0xE0];
    void *holder;
};
struct SightSelf {
    unsigned char prefix[0x10];
    struct SightOwner *owner;
    unsigned char gap14[0x38 - 0x14];
    struct SightTarget *target;
};
typedef int (*RayFilter)(void *context, void *record);
extern char D_00475480[];
int func_00170500(void *holder, void *key);
Qword func_00134FF8(struct SightSelf *self);
int func_0025CEC8(void *context, void *record);
void func_0025CF18(void *game, Qword start, Qword end, RayFilter filter, void *context, int *count, void ***records);
void *func_00165000(int flags, Qword start, Qword end, int count, void **records, void *output);
int func_001349C8(struct SightSelf *self)
{
    void *frame;
    int count;
    void **records;
    Qword start, end;
    if(!self->target) return 1;
    if(!func_00170500(self->owner->holder, self->target)) return 1;
    start = func_00134FF8(self);
    end = *(Qword *)(self->target->table[36].fn((char *)self->target + self->target->table[36].delta) + 0x30);
    func_001D2770(&frame);
    func_0025CF18(D_00475480, start, end, func_0025CEC8, self->owner->context, &count, &records);
    if(func_00165000(0, start, end, count, records, 0)) {
        func_001D2798(&frame, 2);
        return 1;
    }
    func_001D2798(&frame, 2);
    return 0;
}
