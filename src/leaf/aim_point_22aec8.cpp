// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Report the aim point and radius of the controller's subject for a target object: the point comes from the target (path closest
// point for kind-9 targets) or from the subject itself, with its own radius, or the heading angle of its matrix row.
#include "../P2/state_position_ops.h"
struct Matrix { VECTOR4 rows[4]; };
struct Method { short delta, reserved; Matrix *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; Method *methods; };
struct Subject : Object {
    unsigned char pad10[0x1BC - 0x10]; float radius;
    unsigned char pad1C0[0x260 - 0x1C0]; qword offset;
};
struct Controller { unsigned char pad00[0x28]; Subject *primary; unsigned char pad2C[0x4C - 0x2C]; Subject *secondary; };
extern "C" int func_0013B500(void *object, int kind);
extern "C" void func_0022EA88(void *path, qword point, int space, qword *position, qword *direction, int a, int b);
extern "C" float func_001205C8(qword vector);
extern "C" float func_002A3EE8(float y, float x);
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
#define MATRIX(o) ((o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
extern "C" void func_0022AEC8(Controller *self, Object *target, qword *outPosition, float *outRadius)
{
    Subject *base = self->primary;
    qword position;
    float radius;
    if (!base)
        base = self->secondary;
    if (target) {
        if (func_0013B500(target, 9)) {
            qword direction;
            func_0022EA88(target, *(qword *)&MATRIX(base)->rows[3], 0, &position, &direction, 0, 0);
            radius = func_001205C8(direction);
        } else {
            position = *(qword *)&MATRIX(target)->rows[3];
            float *row = (float *)MATRIX(target);
            radius = func_002A3EE8(row[1], row[0]);
        }
    } else {
        position = *(qword *)&MATRIX(base)->rows[3];
        if (func_0013B500(base, 0x32)) {
            position = Add(position, base->offset);
            radius = base->radius;
        } else {
            float *row = (float *)MATRIX(base);
            radius = func_002A3EE8(row[1], row[0]);
        }
    }
    if (outPosition) *outPosition = position;
    if (outRadius) *outRadius = radius;
}
