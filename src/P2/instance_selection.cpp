// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Pick the last equally ranked usable entry, or apply the mode-one head rule.
#include "instance_selection.h"

extern "C" INSTANCE_SELECTION_ENTRY *
func_001FBA28(INSTANCE_SELECTION_OWNER *owner, int minimum)
{
    int index, value, best_value;
    INSTANCE_SELECTION_ENTRY *entry, *best;
    if (owner->mode == 1 && owner->head) {
        if (func_001FB620(owner, owner->head) < 3)
            return 0;
        best = owner->head;
    } else {
        best_value = minimum;
        best = 0;
        for (index = owner->table->first; index < owner->table->capacity; index++) {
            entry = func_001FB600(owner, index);
            value = func_001FB620(owner, entry);
            if (value >= best_value) {
                best = entry;
                best_value = value;
            }
        }
    }
    return best;
}
