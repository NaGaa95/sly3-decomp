// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00232F60: follower re-aim: snap to the target, derive the swing angle from the distance and rebuild both bases.
#include "../P2/state_position_ops.h"
struct Matrix { VECTOR4 rows[4]; };
struct Method { short delta, reserved; Matrix *(*call)(void *); };
struct Follower {
    unsigned char pad00[0xC]; Method *methods;
    unsigned char pad10[0x144 - 0x10]; void *link;
    unsigned char pad148[0x178 - 0x148]; float angleA, angleB; VECTOR4 position;
    VECTOR4 upA; MATRIX3 basisA; MATRIX3 basisB; VECTOR4 upB;
    unsigned char pad210[0x270 - 0x210]; VECTOR4 target;
    unsigned char pad280[0x288 - 0x280]; float minimumAngle, range, scale;
};
extern VECTOR4 D_00317530;
extern VECTOR4 D_00317560;
extern "C" void func_00232A38(Follower *self, int mode);
extern "C" void func_0011CBA0(MATRIX3 *r, qword v);
extern "C" void func_00239CE8(void *link, int id);
#define MATRIX(o) ((o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
union Vec { qword q; float f[4]; };
extern "C" void func_00232F60(Follower *self)
{
    Vec scaleVec;
    MATRIX3 basis;
    qword aim;
    func_00232A38(self, 2);
    aim = *(qword *)&self->target;
    *(qword *)&self->position = aim;
    qword diff = PackedDifference(aim, *(qword *)&MATRIX(self)->rows[3]);
    qword *pup = (qword *)&self->upA;
    register qword d __asm__("vf1"); /* pin: the length vector lives in vf1 */
    qword one;
    float length;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(diff));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(d));
    __asm__("mtc1 %1,%0" : "=f"(length) : "r"(d));
    float angle = length / self->range;
    angle = angle < self->minimumAngle ? self->minimumAngle : angle;
    self->angleA = angle;
    self->angleB = angle;
    qword fallback = *(qword *)&D_00317530;
    qword direction;
    if (length < 0.0001f)
        direction = fallback;
    else {
        __asm__("vdiv $Q,$vf0w,%0x\n\tvwaitq" : : "j"(d));
        __asm__("vmulq.xyzw %0,%1,$Q" : "=j"(direction) : "j"(diff));
    }
    qword scaleQ;
    // VU_FLOAT-style load: the never-chosen "V" alternative keeps the float a MEM until reload (as in Sly 2 func_001BFF28)
    __asm__("qmtc2.ni %1,%0" : "=j,j"(scaleQ) : "r,V"(self->scale));
    scaleVec.q = scaleQ;
    qword upper;
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(upper) : "j"(direction), "j"(scaleQ));
    *pup = upper;
    self->upB = D_00317560;
    func_0011CBA0(&basis, diff);
    self->basisA = basis;
    self->basisB = basis;
    func_00239CE8(self->link, 0xA4);
}
