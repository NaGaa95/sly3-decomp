// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Follower reset variant that starts from a stored source frame: take the source position/up vectors/basis, aim the first
// basis at it from the owner (translation row of the virtual-slot-36 matrix) and scale the start angle by the distance
// (distance / range, at least minimumBase + minimumExtra); same setup as func_00232E88 with mode 3 and event 0x9F.
#include "../P2/state_position_ops.h"
struct Matrix { VECTOR4 rows[4]; };
struct Method { short delta, reserved; Matrix *(*call)(void *); };
struct Follower {
    unsigned char pad00[0xC]; Method *methods;
    unsigned char pad10[0x144 - 0x10]; void *link;
    unsigned char pad148[0x178 - 0x148]; float angleA, angleB; VECTOR4 position;
    VECTOR4 upA; MATRIX3 basisA; MATRIX3 basisB; VECTOR4 upB;
    unsigned char pad210[0x210 - 0x210]; qword sourcePosition; VECTOR4 sourceUpA; VECTOR4 sourceUpB; MATRIX3 sourceBasis;
    unsigned char pad270[0x294 - 0x270]; float minimumBase, minimumExtra, range;
};
extern "C" void func_00232A38(Follower *self, int mode);
extern "C" void func_0011CBA0(MATRIX3 *r, qword v);
extern "C" void func_00239CE8(void *link, int id);
#define MATRIX(o) ((o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
static inline float LengthXYZ(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%2
	vaddw.x %1,$vf0,$vf0w
	vadday.x $ACC,%0,%0y
	vmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%0x
	vwaitq
	vaddq.x %0,$vf0,$Q" : "+j"(d));
    float result;
    __asm__("mtc1 %1,%0" : "=f"(result) : "r"(d));
    return result;
}
extern "C" void func_00233098(Follower *self)
{
    qword aim;
    MATRIX3 basis;
    func_00232A38(self, 3);
    aim = self->sourcePosition;
    *(qword *)&self->position = aim;
    self->basisB = self->sourceBasis;
    self->upA = self->sourceUpA;
    self->upB = self->sourceUpB;
    qword diff = PackedDifference(aim, *(qword *)&MATRIX(self)->rows[3]);
    float angle = LengthXYZ(diff) / self->range;
    float minimum = self->minimumBase + self->minimumExtra;
    angle = angle < minimum ? minimum : angle;
    self->angleA = angle;
    self->angleB = angle;
    func_0011CBA0(&basis, diff);
    self->basisA = basis;
    func_00239CE8(self->link, 0x9F);
}
