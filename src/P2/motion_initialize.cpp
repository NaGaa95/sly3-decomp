// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "common.h"
#include "owner_parent_link.h"

typedef int MotionWord __attribute__((mode(TI)));
struct MotionEntry { short delta, reserved; void (*method)(void *); };
struct MotionObject {
    char prefix[0xC]; MotionEntry *table;
    char reserved10[0x138 - 0x10]; float delay;
    char reserved13C[0x168 - 0x13C]; float deadline;
    char reserved16C[0x188 - 0x16C]; int counter;
};
extern "C" {
extern char D_00317490[];
extern MotionWord D_00317560;
extern const float D_00325570;
extern float D_0036BB98;

void func_001F8138(MotionObject *object, MotionWord position, MotionWord velocity,
                   float delay, float duration)
{
    MotionEntry *entry = &object->table[8];
    entry->method((char *)object + entry->delta);
    func_001C7A00(object, 0, 0);
    entry = &object->table[34];
    ((void (*)(void *, MotionWord))entry->method)
        ((char *)object + entry->delta, position);
    entry = &object->table[35];
    ((void (*)(void *, const void *))entry->method)
        ((char *)object + entry->delta, D_00317490);
    entry = &object->table[40];
    ((void (*)(void *, MotionWord))entry->method)
        ((char *)object + entry->delta, velocity);
    entry = &object->table[41];
    ((void (*)(void *, MotionWord))entry->method)
        ((char *)object + entry->delta, D_00317560);
    object->delay = delay;
    object->counter = 0;
    entry = &object->table[80];
    ((void (*)(void *, int))entry->method)
        ((char *)object + entry->delta, 2);
    object->deadline = duration == D_00325570 ? D_00325570 : D_0036BB98 + duration;
}
}
