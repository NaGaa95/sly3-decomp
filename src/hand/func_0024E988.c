// When the original state permits, compute the angle from the explicit three-column matrix and copy its complete48 aligned bytes.11D4F8 consumes only matrix A0 and returns actual float F0.
// Reference algorithm: src/hand/func_00182FE8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
struct Matrix3 {QWORD column[3];};
struct S {char prefix[0x1B4];int state;int unused;float angle;struct Matrix3 matrix;};
float func_0011D4F8(const struct Matrix3 *matrix);
void func_0024E988(struct S *p,const struct Matrix3 *matrix){if(!p->state){p->angle=func_0011D4F8(matrix);p->matrix=*matrix;}}
