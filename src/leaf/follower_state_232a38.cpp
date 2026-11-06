// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Follower state change: on the first change remember the owner position/basis and the two slot values (virtual slots 36/38/39),
// then record the new state (-1..4) and run its entry action (effect start/stop through func_00137588, mode reset, final cleanup).
#include "../P2/state_position_ops.h"
struct Matrix { VECTOR4 rows[4]; };
struct Method { short delta, reserved; void *call; };
struct Follower {
    unsigned char pad00[0xC]; Method *methods;
    unsigned char pad10[0x130 - 0x10]; int index130;
    unsigned char pad134[0x138 - 0x134]; void *object138;
    unsigned char pad13C[0x144 - 0x13C]; void *link144;
    unsigned char pad148[0x14C - 0x148]; void *object14C;
    unsigned char pad150[0x154 - 0x150]; void *object154; void *object158;
    unsigned char pad15C[0x168 - 0x15C]; int link;
    int state;
    unsigned char pad170[0x17C - 0x170]; float timer;
    unsigned char pad180[0x210 - 0x180]; qword position;
    qword value220; qword value230; MATRIX3 basis;
    unsigned char pad270[0x2B0 - 0x270]; float f2B0;
};
extern char D_0036C700[];
extern "C" void func_001C7A00(Follower *self, int index, int arg);
extern "C" void func_001C8FB0(Follower *self, int index);
extern "C" void func_00137628(int *link);
extern "C" void func_00137588(void *effect, Follower *self, float a, float b, int kind, int *link);
extern "C" void func_00138B68(void *object, float value);
extern "C" void *func_00233668(Follower *self);
extern "C" void func_00239CE8(void *link, int id);
extern "C" void func_001FE728(void *object, int arg);
extern "C" void func_001854C8(void *table, int id, Follower *self);
#define CALL_PTR(o, slot) (((void *(*)(void *))(o)->methods[slot].call)((unsigned char *)(o) + (o)->methods[slot].delta))
#define CALL_QWORD(o, slot) (((qword (*)(void *))(o)->methods[slot].call)((unsigned char *)(o) + (o)->methods[slot].delta))
#define CALL_VOID(o, slot) (((void (*)(void *))(o)->methods[slot].call)((unsigned char *)(o) + (o)->methods[slot].delta))
extern "C" void func_00232A38(Follower *self, int mode)
{
    if (self->state == 0) {
        self->position = *(qword *)&((Matrix *)CALL_PTR(self, 36))->rows[3];
        self->basis = *(MATRIX3 *)CALL_PTR(self, 36);
        self->value220 = CALL_QWORD(self, 38);
        self->value230 = CALL_QWORD(self, 39);
        func_001C7A00(self, 0, 15);
        func_00138B68(self->object138, 0.0f);
    }
    self->state = mode;
    switch (mode) {
    case -1:
        func_00137628(&self->link);
        break;
    case 0:
        func_00138B68(self->object138, 0.0f < self->timer ? self->f2B0 : 1.0f);
        func_001C7A00(self, self->index130, 0);
        func_001C8FB0(self, self->index130);
        func_00137588(func_00233668(self), self, 0.0f, 1.0f, 9, &self->link);
        break;
    case 1:
        func_00137588(self->object154, self, 0.0f, 1.0f, 1, &self->link);
        break;
    case 2:
        func_00137588(self->object158, self, 0.0f, 1.0f, 9, &self->link);
        break;
    case 3:
        func_00137588(func_00233668(self), self, 0.0f, 1.0f, 9, &self->link);
        break;
    case 4:
        func_00239CE8(self->link144, 0x9F);
        if (self->object14C)
            func_001FE728(self->object14C, 1);
        CALL_VOID(self, 9);
        func_001854C8(D_0036C700, 0x10, self);
        break;
    }
}
