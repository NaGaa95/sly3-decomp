// Complete original function, inputs and emitted data independently reviewed.
// Repeat the state transition until stable, preserving the actual cooldown and input-query fields.
// SLY3_CFLAGS: -Os -G0
struct ACTOR_GATE {
    char pad0[0x134];
    void *input;
    char pad138[0xF78 - 0x138];
    int phase;
    char padF7C[0x10D4 - 0xF7C];
    int identifier;
    char pad10D8[0x1134 - 0x10D8];
    void *lookup;
    char pad1138[8];
    void *target;
    char pad1144[0x1520 - 0x1144];
    int mode;
    char pad1524[0x18F0 - 0x1524];
    int state;
    char pad18F4[0x1920 - 0x18F4];
    float cooldownStart;
    char pad1924[0x1940 - 0x1924];
    int enabled;
};
extern float D_0036BB98;
int func_00156998(void *actor);
void func_0013F970(void *actor, int state);
#include "input_query_api.h"
void func_0013EB68(void *actor, unsigned int flags);
int func_00239A78(void *lookup, int identifier);
void func_0023A070(void *target, int identifier);
void func_0013F990(struct ACTOR_GATE *actor) {
    int oldState;
    do {
        oldState = actor->state;
        switch (oldState) {
            case 0: case 1: if (!func_00156998(actor)) {
                func_0013F970(actor, -1);
            }
            else if (actor->state == 1) {
                if (2.0f < D_0036BB98 - actor->cooldownStart) func_0013F970(actor, 0);
            }
            else {
                void *input = actor->input;
                if (func_001A7A80(input, 8, 0.25f)) func_0013EB68(actor, 0x80000);
            }
            break;
            case -1: if (func_00156998(actor) && actor->phase != 2) {
                if (2.0f < D_0036BB98 - actor->cooldownStart) func_0013F970(actor, 0);
                else func_0013F970(actor, 1);
            }
            if (actor->mode == 0 && actor->enabled && actor->identifier != -1 && actor->target && func_00239A78(actor->lookup, 0x199) >= 0) func_0023A070(actor->target, 0x199);
            break;
        }
    }
    while (oldState != actor->state);
}
