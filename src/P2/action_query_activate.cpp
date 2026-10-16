// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "action_query_shared.h"
static inline qword OwnerPosition(ActionQueryOwner *owner)
{
    SCENE_VIRTUAL_ENTRY *entry = &owner->scene.vtable[36];
    MATRIX4 *matrix = static_cast<MATRIX4 *>(entry->Query(reinterpret_cast<char *>(owner)+entry->delta));
    return *reinterpret_cast<qword *>(&matrix->mat[3]);
}
extern "C" void func_00181F68(ActionQueryState *state)
{
    func_00238978();
    if (state->owner->flags1144&4) {
        qword first = OwnerPosition(state->owner);
        qword second = OwnerPosition(state->owner);
        ActionQueryScopeRecord *record = state->owner->link?state->owner->link->record:0;
        void *context = record?record->context:0;
        void *query = func_001EF038(first, second, context);
        func_001825C0(state, 1, query);
    } else {
        func_001825C0(state, 0, 0);
    }
}
