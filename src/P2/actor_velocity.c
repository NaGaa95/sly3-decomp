// SLY3_CFLAGS: -Os -G0
#include "common.h"
struct ActorVelocityMethod {
    short adjustment, reserved;
    void *function;
};
struct ActorVelocityView {
    unsigned char prefix[0xC];
    struct ActorVelocityMethod *table;
};
struct ActorVelocityProperty {
    unsigned char prefix[0x50];
    int mode;
};
int func_002533C0(void *, int);
void *func_002387A8(void *, int);
void func_0016D840(void *, int);
void func_0016E118(void *, int);
qword func_001205F0(qword, float);

void func_00255960(void *receiver)
{
    struct ActorVelocityView *object = receiver;
    if (func_002533C0(receiver, 0x25) || func_002533C0(receiver, 0x26)) {
        func_0016D840(func_002387A8((char *)receiver + 0x29C, 0xD9), 2);
    } else {
        struct ActorVelocityProperty *property;
        if (!func_002533C0(receiver, 0x2A))
            return;
        property = func_002387A8((char *)receiver + 0x29C, 0xDA);
        if (property->mode != 3 && property->mode != 6)
            func_0016E118(property, 2);
    }
    {
        struct ActorVelocityMethod *method = object->table + 38;
        qword velocity = ((qword (*)(void *))method->function)
            ((char *)object + method->adjustment);
        velocity = func_001205F0(velocity, 800.0f);
        method = object->table + 40;
        ((void (*)(void *, qword))method->function)
            ((char *)object + method->adjustment, velocity);
    }
}
