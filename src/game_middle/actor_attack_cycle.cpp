// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "activation_selector_api.h"
#include "input_query_api.h"
#include "../P2/input_mask.h"

struct ActorAttackCycle {
    unsigned char opaque00[0x130];
    int slot_index;
    void *input;
    unsigned char opaque138[0x1140 - 0x138];
    void *request;
    unsigned char opaque1144[0x1668 - 0x1144];
    float remaining, last_trigger;
    int triggers;
    void *secondary_request;
    int variant;
};

extern "C" {
extern unsigned char D_00475480[];
extern int D_003465D0[][5], D_00346610[][5];
int func_001A9478(void *manager, int index);

void func_001DDE80(ActorAttackCycle *actor)
{
    int identifier;
    if (actor->slot_index == -1) return;
    if (func_001A9478(D_00475480, actor->slot_index)) return;
    identifier = func_00239E70(actor->request);
    if (identifier != func_00239E50(actor->request)) return;
    if (identifier >= 0x1FE) return;
    if (identifier < 0x1F9) return;
    actor->remaining -= D_0036BB98.step;
    if (func_001A7A80(actor->input, 0xF0, 0.0f)) {
        actor->triggers--;
        actor->last_trigger = actor->remaining;
    }
    if (actor->remaining <= 0.0f) {
        if (actor->triggers <= 0)
            identifier = D_003465D0[actor->variant][identifier - 0x1F9];
        else
            identifier = D_00346610[actor->variant][identifier - 0x1F9];
    } else if (actor->last_trigger - actor->remaining > 1.0f) {
        identifier = 0x1F8;
    }
    if (actor->secondary_request)
        func_00239CE8(actor->secondary_request, identifier);
    func_00239CE8(actor->request, identifier);
}
}
