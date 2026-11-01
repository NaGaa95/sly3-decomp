// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Follower basis at `time`: before the start window the first basis (+0x1A0), after the end the second one (+0x1D0), inside the
// start/end windows a blend computed by func_00118740 from the owner matrix (slot 36) and frame (slot 39); also gives the up vector.
#include "../P2/state_position_ops.h"
struct Matrix { VECTOR4 rows[4]; };
struct Method { short delta, reserved; void *call; };
struct Follower {
    unsigned char pad00[0xC]; Method *methods;
    unsigned char pad10[0x178 - 0x10]; float angleA, angleB; VECTOR4 position;
    VECTOR4 upA; MATRIX3 basisA; MATRIX3 basisB; VECTOR4 upB;
};
extern VECTOR4 D_00317560;
extern "C" void func_00118740(float a, float b, float c, void *matrix, qword frame, MATRIX3 *basis, qword up, MATRIX3 *outBasis, VECTOR4 *outUp);
#define CALL_PTR(o, slot) (((void *(*)(void *))(o)->methods[slot].call)((unsigned char *)(o) + (o)->methods[slot].delta))
#define CALL_QWORD(o, slot) (((qword (*)(void *))(o)->methods[slot].call)((unsigned char *)(o) + (o)->methods[slot].delta))
static inline float Max(float a, float b) { return a < b ? b : a; }
extern "C" void func_00233360(Follower *self, MATRIX3 *outBasis, VECTOR4 *outUp, float time, float inWindow, float outWindow)
{
    float remaining = self->angleB - time;
    if (remaining <= 0.0f) {
        if (outBasis) *outBasis = self->basisB;
        if (outUp) *outUp = self->upB;
    } else if (remaining < outWindow) {
        float blend = Max(time, self->angleB);
        void *matrix = CALL_PTR(self, 36);
        qword frame = CALL_QWORD(self, 39);
        func_00118740(blend, time, 1.0f, matrix, frame, &self->basisB, *(qword *)&self->upB, outBasis, outUp);
    } else {
        float elapsed = self->angleA - remaining;
        if (elapsed < inWindow) {
            float blend = Max(time, inWindow - elapsed);
            void *matrix = CALL_PTR(self, 36);
            qword frame = CALL_QWORD(self, 39);
            func_00118740(blend, time, 1.0f, matrix, frame, &self->basisA, *(qword *)&D_00317560, outBasis, outUp);
        } else {
            if (outBasis) *outBasis = self->basisA;
            if (outUp) *outUp = D_00317560;
        }
    }
}
