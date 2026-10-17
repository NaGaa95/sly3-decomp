// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/state_position_ops.h"
struct DistancePoint { qword position; };
union DistanceBits { float real; int bits; };
struct DistanceEntry { DistancePoint *point; int distanceBits; };
struct DistanceItem {
    qword origin;
    int count;
    DistanceEntry *entries;
    char tail[8];
};
struct DistanceSet { int count; DistanceItem *items; };
extern "C" void func_001ED0E0(DistanceSet *set)
{
    int i, j;
    for (i = 0; i < set->count; i++) {
        DistanceItem *item = &set->items[i];
        for (j = 0; j < item->count; j++) {
            DistanceEntry *entry = &item->entries[j];
            DistanceBits distance;
            distance.real = PackedHorizontalLength(PackedDifference(item->origin, entry->point->position));
            entry->distanceBits = distance.bits;
        }
    }
}
