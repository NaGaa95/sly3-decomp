// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Reset the follower's tracking state: base setup (func_00232A38), remember the owner position (translation row of its
// virtual-slot-36 matrix), clear two direction vectors, build the aim basis from the stored target to that position and
// store it in both basis slots, then start both angles at the current spread (+0x280 + +0x284) and notify func_00239CE8.
#include "../P2/state_position_ops.h"
struct Matrix { VECTOR4 rows[4]; };
struct Method { short delta, reserved; Matrix *(*call)(void *); };
struct Follower {
    unsigned char pad00[0xC]; Method *methods;
    unsigned char pad10[0x144 - 0x10]; void *link;
    unsigned char pad148[0x178 - 0x148]; float angleA, angleB; VECTOR4 position;
    VECTOR4 upA; MATRIX3 basisA; MATRIX3 basisB; VECTOR4 upB;
    unsigned char pad210[0x270 - 0x210]; VECTOR4 target;
    float spread, spreadExtra;
};
extern VECTOR4 D_00317560;
extern "C" void func_00232A38(Follower *self, int mode);
extern "C" void func_0011CBA0(MATRIX3 *r, qword v);
extern "C" void func_00239CE8(void *link, int id);
#define MATRIX(o) ((o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
extern "C" void func_00232E88(Follower *self)
{
    qword aim;
    MATRIX3 basis;
    float angle;
    func_00232A38(self, 1);
    self->position = MATRIX(self)->rows[3];
    aim = *(qword *)&self->target;
    self->upA = D_00317560;
    self->upB = D_00317560;
    func_0011CBA0(&basis, PackedDifference(aim, *(qword *)&MATRIX(self)->rows[3]));
    angle = self->spread + self->spreadExtra;
    self->basisA = basis;
    self->angleA = angle;
    self->basisB = basis;
    self->angleB = angle;
    func_00239CE8(self->link, 0xA4);
}
