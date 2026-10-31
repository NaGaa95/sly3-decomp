// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Gate for a flagged segment object: the context mask (+0x1144) must contain the mode's required bits (3 for mode 1, otherwise 2); mode 1 additionally needs the segment's end-minus-start vector to pass the context's query.
#include "../P2/state_position_ops.h"
struct GateSegment {
    char prefix[0x2C];
    unsigned char pad2C[3];
    unsigned char flagByte;
    char gap30[0x110 - 0x30];
    int mode;
    char gap114[0x120 - 0x114];
    qword start;
    qword end;
};
struct GateContext {
    char prefix[0x1144];
    unsigned int mask;
    char gap1148[0x11E4 - 0x1148];
    void *query;
};
extern "C" int func_002591E8(void *query, qword point);
extern "C" int func_001EEFB0(void *unused, GateSegment *segment, GateContext *context)
{
    long byte = segment->flagByte;
    if (((int)byte & 1) == 0)
        return 0;
    int mode = segment->mode;
    unsigned int required = mode == 1 ? 3 : 2;
    if ((required & context->mask) != required)
        return 0;
    if (mode == 1) {
        int hit = func_002591E8(context->query, PackedDifference(segment->end, segment->start));
        if (!hit)
            return 0;
    }
    return 1;
}
