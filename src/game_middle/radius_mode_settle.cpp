// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/state_position_ops.h"
struct SettleRecord { char prefix[0x30]; qword value; };
struct SettlePositionMethod { short delta, reserved; SettleRecord *(*get)(void *receiver); };
struct SettleLink { char prefix[12]; SettlePositionMethod *methods; };
struct SettleModeMethod { short delta, reserved; void (*set)(void *receiver, int inside); };
struct SettleChaser {
    char prefix[12];
    SettleModeMethod *methods;
    SettleLink *link;
    char gap14[0x3C - 0x14];
    int state;
    char gap40[0x48 - 0x40];
    float nearRadius;
    float farRadius;
    char gap50[0x60 - 0x50];
    qword anchor;
};
extern "C" void func_002389A0(void *receiver);
extern "C" void func_001D8140(void *receiver);
extern "C" void func_001D89B0(SettleChaser *chaser)
{
    func_002389A0(chaser);
    func_001D8140(chaser);
    SettlePositionMethod *linkMethod = &chaser->link->methods[36];
    qword position = linkMethod->get((char *)chaser->link + linkMethod->delta)->value;
    int state;
    do {
        state = chaser->state;
        float radius = state == 0 ? chaser->nearRadius : chaser->farRadius;
        int outside = radius < PackedHorizontalLength(PackedDifference(position, chaser->anchor));
        if (outside) {
            SettleModeMethod *method = &chaser->methods[16];
            method->set((char *)chaser + method->delta, 0);
        } else {
            SettleModeMethod *method = &chaser->methods[16];
            method->set((char *)chaser + method->delta, 1);
        }
    } while (chaser->state != state);
}
