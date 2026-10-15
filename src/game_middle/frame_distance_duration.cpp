// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/scene.h"
#include "../P2/state_position_ops.h"

struct DurationSource {
    unsigned char opaque00[0xC];
    SCENE_VIRTUAL_ENTRY *vtable;
    unsigned char opaque10[0x100 - 0x10];
    qword position;
    unsigned char opaque110[0x148 - 0x110];
    float duration;
};
struct DurationFrame { qword row[4]; };

extern "C" {
void func_001C7DC8(void *receiver);
qword func_001C9428(SCENE_OBJECT *source, SCENE_OBJECT *destination, qword position);
}

static inline VUXScalarCarrier SquaredLengthXYZ(qword vector)
{
    qword products, one;
    asm("vmul.xyz %0,%1,%1" : "=j"(products) : "j"(vector));
    asm("vaddw.x %0,$vf0,$vf0w\n\t"
        "vadday.x $ACC,%1,%1y\n\t"
        "vmaddz.x %1,%0,%1z"
        : "=&j"(one), "+j"(products));
    return products;
}

extern "C" void func_001A23F8(void *receiver)
{
    DurationSource *source = (DurationSource *)receiver;
    func_001C7DC8(receiver);
    int default_duration = 1;
    if (source->duration != 1250.0f)
        default_duration = 0;
    if (default_duration) {
        SCENE_VIRTUAL_ENTRY *entry = &source->vtable[36];
        DurationFrame *frame = (DurationFrame *)entry->Query((char *)source + entry->delta);
        qword origin = frame->row[3];
        qword point = func_001C9428((SCENE_OBJECT *)receiver, 0, source->position);
        qword difference = PackedDifference(origin, point);
        source->duration = PackedSquareRootX(SquaredLengthXYZ(difference)) + 1000.0f;
    }
}

extern "C" {
extern char D_00479B50[];
void func_0011AF60(void *list, void *receiver);
void func_0011B028(void *list, void *receiver);

void func_001A24C0(void *receiver)
{
    func_0011AF60(D_00479B50, receiver);
}

void func_001A24E8(void *receiver)
{
    func_0011B028(D_00479B50, receiver);
}
}
