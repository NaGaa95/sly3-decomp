// Complete original USA actor query; generic external receiver and actual private field view.
// SLY3_CFLAGS: -Os -G0
#include "actor_input_query.h"
struct CurrentState { char unknown[0x78]; int mode; };
struct State {
    char unknown[0x130]; int selection;
    char gap[0x10D4-0x134]; int readiness; int unknown10D8;
    struct CurrentState *current;
};
extern char D_00475480[];
int func_001A9478(void *,int);

int func_001530F8(void *receiver) {
    struct State *state = (struct State *)receiver;
    if (func_001A9478(D_00475480, state->selection))
        return 0;
    if (state->readiness != -1) {
        if (state->current->mode)
            return 1;
    }
    return -1;
}

