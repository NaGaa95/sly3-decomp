// SLY3_CFLAGS: -Os -G0
#include "actor_state_resource_api.h"
struct AudioFloatRange { float low, high; };
struct AudioRangeEntry {
    void *target;
    struct AudioFloatRange range;
    float scale;
};
struct AudioRangeReceiverView {
    unsigned char prefix[0xA0];
    int counts[6];
    struct AudioRangeEntry entries[6][8];
};
void func_00245320(void *, unsigned short, unsigned short);

void func_002462B8(void *receiver, int index, void *target, float scale, float *range)
{
    struct AudioRangeReceiverView *audio = receiver;
    if ((unsigned int)index < 6 && audio->counts[index] < 8) {
        struct AudioRangeEntry *entry;
        func_00245320(receiver, 0x200, 0x200);
        entry = &audio->entries[index][audio->counts[index]++];
        entry->target = target;
        entry->scale = scale;
        entry->range = *(struct AudioFloatRange *)range;
        if (entry->range.low == entry->range.high)
            entry->range.high += 1.0f;
    }
}
