// Complete original inputs, full body and emitted sections independently reviewed.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct SELECTION_OWNER {
    char unused_00[0x48];
    void *command;
    void *actor;
};
extern void func_00156468(void *actor, void *owner);
#include "script_actor_binding_api.h"
void func_0022B028(void *context, void *command, void *actor) {
    struct SELECTION_OWNER *owner = (struct SELECTION_OWNER *)context;
    if (command != owner->command) owner->command = command;
    if (actor != owner->actor) {
        if (owner->actor) func_00156468(owner->actor, 0);
        owner->actor = actor;
        if (actor) func_00156468(actor, owner);
    }
}
