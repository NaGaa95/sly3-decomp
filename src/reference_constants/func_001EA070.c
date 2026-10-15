// Original USA state predicate; full integer helper result is retained.
// The fallback applies only to -1 with the original field exactly equal to1.
// Separate adjacent descriptor getter1EA0B8 is excluded from this body.
// SLY3_CFLAGS: -Os -G0
struct State {
    char unknown[0x1470];
    int fallback;
};
#include "actor_input_query.h"
int func_001EA070(struct State *state) {
    int value = func_001530F8(state);
    if (value == -1)
        return state->fallback == 1 ? 1 : value;
    return value;
}
