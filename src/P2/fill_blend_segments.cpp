// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "animation_record_lookup_api.h"
struct BlendChild { char prefix[0x64]; float duration; };
struct BlendEntry { int unused; BlendChild *child; };
struct BlendSegment { float time, duration; };
extern "C" void func_00148468(int stride,int count,void *entries,int segment_offset,
                              int key_count,const int *keys)
{
    for (int i = 0; i < count; ++i) {
        BlendEntry *entry = (BlendEntry *)((char *)entries + i * stride);
        BlendChild *child = entry->child;
        if (child) {
            BlendSegment *segments = (BlendSegment *)((char *)entry + segment_offset);
            BlendSegment *previous;
            BlendSegment *segment;
            int k;
            segment = segments;
            for (k = 0; k < key_count; ++k, ++segment)
                segment->time = func_001368E0(
                    static_cast<LookupLibrary *>(static_cast<void *>(child)),keys[k]);
            unsigned int last_offset = (unsigned int)key_count * sizeof(BlendSegment) - sizeof(BlendSegment);
            segment = segments;
            previous = (BlendSegment *)((unsigned int)segment + last_offset);
            for (k = 0; k < key_count; ++k, ++segment) {
                float duration = segment->time - previous->time;
                previous->duration = duration;
                if (duration < 0.0f)
                    previous->duration = duration + child->duration;
                previous = segment;
            }
        }
    }
}
