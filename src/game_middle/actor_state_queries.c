// Return the inherited actor query, then apply this actor's fallback states.
// SLY3_CFLAGS: -Os -G0
// Reference algorithms: Sly2 hand/func_00189488.c and hand/func_001894F8.c.
#include "actor_input_query.h"

// Only the observed receiver prefix is declared; no concrete class is inferred.
struct ActorView {
    char prefix[0x19E0];
    int state;
};

int func_001AAC30(struct ActorView *p) {
    int result = func_001530F8(p);
    if (result != -1)
        return result;
    switch (p->state) {
    case 2:
    case 6:
    case 7:
        return 1;
    }
    return -1;
}

int func_001AACA0(struct ActorView *p) {
    switch (p->state) {
    case 0:
    case 1:
    case 2:
    case 6:
    case 10:
    case 19:
        return 1;
    }
    return 0;
}
