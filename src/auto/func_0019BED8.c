#include "state_transition_api.h"
#include "m2c_prelude.h"

void func_001F3C80(void *receiver);                            /* extern */

void func_0019BED8(s32 arg0) {
    func_001F3C80((void *)arg0);
    func_0019C570((struct StateTransitionOwner *)arg0, -1);
}
