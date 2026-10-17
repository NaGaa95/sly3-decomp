// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/state_position_ops.h"
struct RadiusPosition { char prefix[0x30]; qword value; };
struct RadiusMethod { short delta, reserved; RadiusPosition *(*get)(void *receiver); };
struct RadiusLink { char prefix[12]; RadiusMethod *methods; };
struct RadiusProbe {
    char prefix[0x10];
    RadiusLink *link;
    char gap14[0x44 - 0x14];
    float radius;
    char gap48[0x90 - 0x48];
    qword position;
};
extern "C" int func_001D8AC0(RadiusProbe *probe)
{
    RadiusLink *link = probe->link;
    RadiusMethod *method = &link->methods[36];
    qword point = method->get((char *)link + method->delta)->value;
    return PackedHorizontalLength(PackedDifference(point, probe->position)) <= probe->radius;
}
