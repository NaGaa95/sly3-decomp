// Complete original function, inputs and emitted data independently reviewed.
// PRIVATE: original state dispatch; full input/table contracts remain under review.
// SLY3_CFLAGS: -Os -G0
#include "actor_state_resource_api.h"
typedef struct {
    short delta;
    short reserved;
    void (*function)(void *, int);
}
VirtualEntry;
struct Payload {
    char opaque0[0x11C];
    int kind11C;
    char opaque120[0x148 - 0x120];
    int state148;
};
struct Actor {
    char opaque0[0xC];
    VirtualEntry *vtable;
    char opaque10[0x500 - 0x10];
    char context500[0x101C - 0x500];
    struct Payload *payload101C;
    float value1020;
    char opaque1024[0x19F4 - 0x1024];
    struct Payload *payload19F4;
};
struct SecondaryActor {
    char opaque0[0x15E0];
    struct Payload *payload15E0;
};
struct Request {
    struct Actor *actor;
    int word4;
    int word8;
    struct Payload *payload;
    int word10;
    float value14;
    int word18;
    int kind1C;
};
extern struct SecondaryActor *D_0046FF30;
void func_001ADDD0(struct Actor *actor, int mode, int argument);
void func_0013E510(struct Actor *actor, int mode);
void func_0022CA70(struct SecondaryActor *actor, int mode);
#define PayloadRecord(pointer, offset) ((pointer) ? (void *)((char *)(pointer) + (offset)) : (void *)0)
void func_001BD520(struct Request *request) {
    switch (request->kind1C) {
        case 8: func_001B40F0(request->actor->context500, 1, request->payload, PayloadRecord(request->payload, 0x130));
        break;
        case 12: func_001B40F0(request->actor->context500, 0, request->payload, PayloadRecord(request->payload, 0x180));
        break;
        case 13: func_001B40F0(request->actor->context500, 0, request->payload, PayloadRecord(request->payload, 0xD0));
        break;
        case 14: func_001B40F0(request->actor->context500, request->payload->kind11C, request->payload, PayloadRecord(request->payload, 0xD0));
        break;
        case 10: func_001B40F0(request->actor->context500, 4, request->payload, PayloadRecord(request->payload, 0xD0));
        break;
        case 11: func_001B40F0(request->actor->context500, 3, request->payload, PayloadRecord(request->payload, 0x180));
        break;
        case 15: {
            struct Actor *actor = request->actor;
            actor->payload19F4 = request->payload;
            if (actor->payload19F4->state148 == 3) func_001ADDD0(actor, 0x11, -1);
            else func_001ADDD0(actor, 4, 1);
            break;
        }
        case 16: request->actor->payload101C = request->payload;
        request->actor->value1020 = request->value14;
        request->actor->vtable[99].function((char *)request->actor + request->actor->vtable[99].delta, 8);
        break;
        case 19: if (request->actor == D_0036B250) func_0013E510(request->actor, 0xA);
        else func_001ADDD0(D_00370AC0, 0x14, -1);
        break;
        case 17: D_0046FF30->payload15E0 = request->payload;
        func_0022CA70(D_0046FF30, 6);
        break;
        default: func_001B77F8(request, 6, 0);
        break;
    }
}
