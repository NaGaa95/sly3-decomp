// SLY3_CFLAGS: -Os -G0
#include "selection_types.h"

typedef struct Clock {
    char reserved0[0x40];
    float time40;
} Clock;

extern Clock D_0036BB98;
extern char D_00475480[];
void func_00165548(Clock *, int channel, float scale);
void func_001A93C8(void *, int, int);
void func_001A9420(void *, int, int);
void func_00261050(SelectionResource *, int);
void func_00261070(SelectionResource *, int);
void *func_002459F8(int);
void func_00244F08(void *, void *);
void func_002201D8(Selection *);
void func_002200B8(Selection *, int);

#define CALL_RECEIVER(p, slot) \
    ((void (*)(void *))(p)->vtable[slot].function)( \
        (char *)(p) + (p)->vtable[slot].adjustment)

void func_00220590(Selection *owner, int state)
{
    if (!owner->child)
        state = -1;
    if (state == owner->state)
        return;
    if (owner->state == -1) {
        func_00165548(&D_0036BB98, 0, 0.0f);
        func_001A93C8(D_00475480, -1, 0);
        func_00261070(owner->child, 1);
    }
    owner->state = state;
    owner->changed_at = D_0036BB98.time40;
    switch (state) {
    case -1:
        CALL_RECEIVER(owner->child, 54);
        func_00165548(&D_0036BB98, 0, 1.0f);
        func_001A9420(D_00475480, -1, 0);
        CALL_RECEIVER(owner, 11);
        if (owner->child->state48 > 0)
            func_00261050(owner->child, 1);
        owner->value280 = state;
        owner->value284 = state;
        owner->value288 = state;
        break;
    case 0:
        owner->child->value64 = 0x561;
        owner->child->value60 = 0x562;
        owner->child->value68 = 0x563;
        func_00261050(owner->child, 2);
        func_00244F08(func_002459F8(0x35), 0);
        break;
    }
    func_002201D8(owner);
    func_002200B8(owner, 0);
    ((void (*)(void *, int))owner->vtable[14].function)(
        (char *)owner + owner->vtable[14].adjustment, -1);
}
