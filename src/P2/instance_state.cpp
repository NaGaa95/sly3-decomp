// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Classify one borrowed instance entry using the minimum state of its objects.
#include "instance_selection.h"

extern "C" int func_001FB620(INSTANCE_SELECTION_OWNER *owner,
                             INSTANCE_SELECTION_ENTRY *entry)
{
    int result, index, j, value;
    if (entry->active)
        return 0;
    if (!entry->owner)
        return 4;
    result = 5;
    index = func_001FB5D8(owner, entry);
    for (j = 0; j < owner->table->object_count; j++) {
        SCENE_OBJECT *object =
            owner->table->objects[index * owner->table->object_count + j];
        int inherited = object->flags.fields.inherited;
        if (!inherited)
            value = 3;
        else if (func_001C8610(object)) {
            result = 1;
            goto out;
        } else
            value = 2;
        if (value < result)
            result = value;
    }
out:
    return result;
}
