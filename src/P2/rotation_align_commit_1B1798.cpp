// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "rotation_matrix_intrinsics.h"
#include "state_position_ops.h"
#include "matrix_algorithms.h"
struct CommitMethod { short delta, reserved; void *(*method)(void *); };
struct CommitMethodTable { unsigned char prefix[0x120]; CommitMethod query; };
struct CommitObject { unsigned char prefix[0xC]; CommitMethodTable *table; };
struct CommitSelf {
    unsigned char prefix0[0xC];
    CommitMethodTable *table;
    unsigned char gap10[0x1BC - 0x10];
    float angle;
    unsigned char gap1C0[0x19F4 - 0x1C0];
    CommitObject *object;
    unsigned char gap19F8[0x1A10 - 0x19F8];
    qword correction;
};
extern qword D_00317550;
extern ROTATION_MATRIX D_00322B90;
extern "C" {
void func_00244828(void *self, qword correction);
void func_0011CDC8(MATRIX3 *output, qword from, qword to);
MATRIX3 *func_0011C8C0(MATRIX3 *matrix, float angle, qword axis);
void func_0023EDE8(void *self, ROTATION_MATRIX matrix, ROTATION_MATRIX *limits);
}
extern "C" void func_001B1798(CommitSelf *self)
{
    qword first[1];
    qword delta[1];
    ROTATION_MATRIX copy;
    ROTATION_MATRIX right;
    ROTATION_MATRIX product;
    ROTATION_MATRIX matrix;
    func_00244828(self, self->correction);
    CommitMethod *entry = &self->object->table->query;
    qword position = *(qword *)((char *)entry->method((char *)self->object + entry->delta) + 0x30);
    first[0] = position;
    CommitMethod *second = &self->table->query;
    delta[0] = PackedDifference(position, *(qword *)((char *)second->method((char *)self + second->delta) + 0x30));
    func_0011CDC8((MATRIX3 *)&matrix, D_00317550, delta[0]);
    copy = matrix;
    func_0011C8C0((MATRIX3 *)&matrix, self->angle, D_00317550);
    right = matrix;
    MultiplyRotation(&matrix, &copy, &matrix);
    product = matrix;
    func_0023EDE8(self, product, &D_00322B90);
}
