// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/heap.h"

struct ActorBoundFrame {
    unsigned char opaque00[4];
    void *first;
    unsigned char opaque08[0x30 - 8];
    void *second;
    unsigned char opaque34[0x80 - 0x34];
    void *third;
    unsigned char opaque84[0xE0 - 0x84];
};
struct ActorFrameBindings {
    unsigned char opaque00[0x1730];
    void *first_position, *first_resource;
    void *second_position, *second_resource;
    unsigned char opaque1740[8];
    ActorBoundFrame *first_frame, *second_frame;
};

extern "C" {
extern unsigned char D_00345FD8[];
void func_00152448(void *actor, void *stream);
void func_001C8970(void *actor, int count, void *bindings, void *owner);
void *func_001D2538(ALLOCREQ *request);
void *func_0023DDA0(void *actor, int identifier, int kind);
void func_001A5EA8(void *frame);
}

static inline ActorBoundFrame *NewBoundFrame()
{
    ALLOCREQ request;
    request.cb = 0xE0;
    request.cbAlign = 0x10;
    return (ActorBoundFrame *)func_001D2538(&request);
}

extern "C" void func_001DCB90(ActorFrameBindings *actor, void *stream)
{
    func_00152448(actor, stream);
    func_001C8970(actor, 0x7F, D_00345FD8, 0);
    actor->first_frame = NewBoundFrame();
    actor->first_frame->first = func_0023DDA0(actor, 0x24C, 6);
    actor->first_frame->second = func_0023DDA0(actor, 0x24D, 6);
    actor->first_frame->third = func_0023DDA0(actor, 0x24E, 1);
    func_001A5EA8(actor->first_frame);
    actor->second_frame = NewBoundFrame();
    actor->second_frame->first = func_0023DDA0(actor, 0x24F, 6);
    actor->second_frame->second = func_0023DDA0(actor, 0x250, 6);
    actor->second_frame->third = func_0023DDA0(actor, 0x251, 1);
    func_001A5EA8(actor->second_frame);
    actor->first_position = actor->first_frame->third;
    actor->first_resource = func_0023DDA0(actor, 0x24E, 6);
    actor->second_position = actor->second_frame->third;
    actor->second_resource = func_0023DDA0(actor, 0x251, 6);
}
