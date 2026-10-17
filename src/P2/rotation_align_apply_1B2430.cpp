// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "rotation_matrix_intrinsics.h"
#include "state_position_ops.h"
#include "matrix_algorithms.h"
struct AlignMethod { short delta, reserved; void *(*method)(void *); };
struct AlignMethodTable { unsigned char prefix[0x120]; AlignMethod query; };
struct AlignObject { unsigned char prefix[0xC]; AlignMethodTable *table; };
struct AlignLink { unsigned char prefix[0xA0]; void *context; };
struct AlignReference { unsigned char prefix[0x70]; qword position; };
struct AlignSelf {
    unsigned char prefix[0x19F4];
    AlignObject *object;
    unsigned char gap19F8[0x1A60 - 0x19F8];
    qword position;
    unsigned char gap1A70[0x1AC8 - 0x1A70];
    AlignLink *link;
    unsigned char gap1ACC[0x1AD4 - 0x1ACC];
    AlignReference *reference;
    unsigned char gap1AD8[0x1B08 - 0x1AD8];
    void *binding;
};
extern qword D_00317530;
extern qword D_00317560;
extern unsigned char D_00322BD0[];
extern float D_0036BB9C;
extern "C" {
qword func_0028E990(void *object, void *context, qword value);
void func_0011CDC8(MATRIX3 *output, qword from, qword to);
MATRIX3 *func_0011C8C0(MATRIX3 *matrix, float angle, qword axis);
void func_0012F4F8(void *receiver, qword value);
qword func_00120C80(qword current, qword target, void *parameters, int mode, float step);
}
extern "C" void func_001B2430(AlignSelf *self)
{
    ROTATION_MATRIX value;
    ROTATION_MATRIX product;
    ROTATION_MATRIX align;
    ROTATION_MATRIX turn;
    AlignObject *object = self->object;
    AlignMethod *entry = &object->table->query;
    qword position = *(qword *)((char *)entry->method((char *)object + entry->delta) + 0x30);
    qword difference = PackedDifference(position, self->reference->position);
    qword direction = func_0028E990(0, self->link->context, difference);
    func_0011CDC8((MATRIX3 *)&align, D_00317530, direction);
    func_0011C8C0((MATRIX3 *)&turn, 1.5f, D_00317530);
    MultiplyRotation(&product, &align, &turn);
    value = product;
    func_0012F4F8(self->binding, func_0011D3C0((const MATRIX3 *)&value));
    self->position = func_00120C80(self->position, D_00317560, D_00322BD0, 0, D_0036BB9C);
}
