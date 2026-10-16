// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "action_query_shared.h"
#include "state_position_ops.h"
static inline qword ScenePosition(SCENE_OBJECT *object)
{
    SCENE_VIRTUAL_ENTRY *entry = &object->vtable[36];
    MATRIX4 *matrix = static_cast<MATRIX4 *>(entry->Query(reinterpret_cast<char *>(object)+entry->delta));
    return *reinterpret_cast<qword *>(&matrix->mat[3]);
}
extern "C" void func_00182450(ActionQueryState *state)
{
    func_002389A0(state);
    if (!state->mode)
        return;
    ActionQueryOwner *owner = state->owner;
    ActionQueryScopeRecord *record = owner->link?owner->link->record:0;
    void *context = record?record->context:0;
    ActionQuerySettings *settings = owner->settings;
    SCENE_OBJECT *reference = settings->reference;
    float bearing = func_00256368(settings);
    qword target = ScenePosition(reference);
    ActionQueryChild *child = state->child;
    if (D_00344FB8<child->distance)
        goto update;
    {
        float pan, radius;
        func_00120B00(PackedDifference(child->position, target), &pan, &radius, 0);
        float angle = __builtin_fabsf(func_0011E3B8(pan-bearing));
        if (settings->angle18<angle)
            goto update;
        if (func_0011EE30(&state->owner->radius, radius))
            return;
    }
update:
    qword first = ScenePosition(&state->owner->scene);
    qword second = func_00182068(state, context, target, bearing);
    void *query = func_001EF038(first, second, context);
    func_001D8B40(child, query);
}
