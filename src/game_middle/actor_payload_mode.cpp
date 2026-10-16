// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "actor_state_resource_api.h"
#include "../P2/input_mask.h"
struct PayloadModeMethod { short adjustment, word2; void *function; };
struct PayloadModeOwner { char unaccessed[0xC]; PayloadModeMethod *methods; };
struct PayloadModeContext {
    PayloadModeOwner *owner;
    float changed;
    int kind;
    char gapC[8];
    void *payload;
    void *record;
    char gap1C[0x500 - 0x1C];
    int pending;
};
extern "C" {
void func_001B4430(void *context, int phase);
void func_001B4290(void *context);
void func_00209470(void *record, int raw_value);
void func_001B40F0(void *context, int kind, void *payload, void *record)
{
    PayloadModeContext *p = (PayloadModeContext *)context;
    int phase;
    func_001B4430(p, -1);
    p->kind = kind;
    p->changed = D_0036BB98.now;
    p->payload = payload;
    p->record = record;
    PayloadModeOwner *owner = p->owner;
    PayloadModeMethod *method = &owner->methods[99];
    ((void (*)(void *, int))method->function)((char *)owner + method->adjustment, 2);
    switch (kind) {
    case 0: case 13:
        phase = 5;
        break;
    case 6:
        phase = 0;
        func_00209470((char *)p->owner + 0x18F0, (int)p->payload);
        break;
    case 5: case 9:
        func_00209470((char *)p + 0x440, (int)p->payload);
        phase = 0;
        break;
    case 8:
        phase = 7;
        func_001B4290(p);
        break;
    case 1:
        phase = 0;
        func_001B4290(p);
        break;
    case 11: case 12:
        phase = 0;
        p->pending = 1;
        break;
    default:
        phase = 0;
        break;
    }
    func_001B4430(p, phase);
}
}
