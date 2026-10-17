// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/state_position_ops.h"

struct PairMethod { short adjustment, word2; void (*function)(void *self, void *frame, int index); };
struct PairVTable { unsigned char prefix[0x1E0]; PairMethod notify; };
struct PairReceiver { unsigned char prefix[0xC]; PairVTable *methods; };
struct PairElement {
    int word0;
    void *source;
    int word8;
    PairReceiver *receiver;
    qword local;
    unsigned char gap20[0x30 - 0x20];
    qword world;
};
struct PairFrame {
    PairElement element[2];
    unsigned char gap80[0xB0 - 0x80];
    qword difference;
};
extern "C" qword func_0028BCD0(void *source, void *unused, qword local);

extern "C" void func_001CBC30(void *unused, int count, PairFrame **frames)
{
    int i, j;
    for (i = 0; i < count; ++i) {
        PairFrame *frame = frames[i];
        PairElement *element = &frame->element[0];
        for (j = 1; j >= 0; --j, ++element) {
            if (element->source)
                element->world = func_0028BCD0(element->source, 0, element->local);
        }
        for (j = 0; j < 2; ++j) {
            PairReceiver *receiver = frame->element[j].receiver;
            if (receiver) {
                PairMethod *method = &receiver->methods->notify;
                method->function((char *)receiver + method->adjustment, frame, j);
            }
        }
        frame->difference = PackedDifference(frame->element[0].world, frame->element[1].world);
    }
}
