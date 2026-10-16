// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/mat.h"
struct ScalarScaleBody {
    MATRIX3 matrix;
    MATRIX3 inverse;
    char unused60[0xD0 - 0x60];
    float coefficient;
};
struct ScalarScaleActor {
    char unused00[0xD8];
    ScalarScaleBody *body;
};
extern "C" void *func_00292034(void *, int, unsigned int);
extern "C" void func_0011C6F8(MATRIX3 *, const MATRIX3 *);

extern "C" void func_001DCCF0(ScalarScaleActor *actor, float gain)
{
    MATRIX3 inverse;
    float coefficient = actor->body->coefficient * 2250.0f;
    ScalarScaleBody *body;
    func_00292034(actor->body, 0, sizeof(MATRIX3));
    actor->body->matrix.mat[0][0] = actor->body->matrix.mat[1][1] =
        actor->body->matrix.mat[2][2] = gain * coefficient;
    body = actor->body;
    func_0011C6F8(&inverse, &body->matrix);
    body->inverse = inverse;
}
