// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Update the body's basis angles from its owner: when the body's embedded record (func_0011AEF8) is not busy, rotate the owner's
// translation row (virtual slot 36) by the stored inverse basis and pass its X/Y components through func_0011EDB8 to func_00237298.
#include "../P2/vector_matrix_intrinsics.h"
struct VTE { short delta, pad; MATRIX4 *(*fn)(void *); };
struct Owner { char pad[0xC]; VTE *vt; };
struct Body { char pad[0x38]; char state[0x18]; Owner *owner; char pad54[0xC]; MATRIX3 inverse; };
extern "C" int func_0011AEF8(void *);
extern "C" float func_0011EDB8(float, float);
extern "C" void func_00237298(Body *, float, float);
union Vec { qword q; float f[4]; };
extern "C" void func_00237FA8(Body *body)
{
    if (!func_0011AEF8(body->state)) {
        Owner *owner = body->owner;
        if (owner) {
            Vec local;
            MATRIX4 *m = owner->vt[36].fn((char *)owner + owner->vt[36].delta);
            local.q = TransformPackedDirection(&body->inverse, *(qword *)m->mat[3]);
            float x = func_0011EDB8(local.f[0], 1.0f);
            float y = func_0011EDB8(local.f[1], 1.0f);
            func_00237298(body, x, y);
        }
    }
}
