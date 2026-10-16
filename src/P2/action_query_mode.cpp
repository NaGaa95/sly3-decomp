// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "action_query_shared.h"
struct ActionQueryIdleChildView {
    char prefix[0xC];
    SCENE_VIRTUAL_ENTRY *table;
    char unknown10[0x38-0x10];
    void *reference;
};
struct ActionQueryTrackChildView {
    char prefix[0xC];
    SCENE_VIRTUAL_ENTRY *table;
    char unknown10[0xB0-0x10];
    int mode;
    char unknownB4[4];
    void *reference;
};
extern "C" {
void *func_00238690(void *pool, int kind);
}
extern "C" void func_001825C0(ActionQueryState *state, int mode, void *query)
{
    if (mode == state->mode)
        return;
    func_00238AE8(&state->child);
    state->mode = mode;
    switch (mode) {
    case 0: {
        ActionQueryIdleChildView *object = static_cast<ActionQueryIdleChildView *>(func_00238690(&state->owner->actions, 0xCA));
        object->reference = state->owner->settings->reference;
        SCENE_VIRTUAL_ENTRY *entry = &object->table[8];
        entry->Simple(reinterpret_cast<char *>(object)+entry->delta);
        break;
    }
    case 1: {
        ActionQueryTrackChildView *object = static_cast<ActionQueryTrackChildView *>(func_00238690(&state->owner->actions, 0xF0));
        func_001D8B40(reinterpret_cast<ActionQueryChild *>(object), query);
        object->mode = 13;
        object->reference = state->owner->settings->reference;
        SCENE_VIRTUAL_ENTRY *entry = &object->table[8];
        entry->Simple(reinterpret_cast<char *>(object)+entry->delta);
        break;
    }
    }
}
