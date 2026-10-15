// Write the difference between the receiver's world translation and the other object's original packed position when a destination is supplied.
// Complete original inputs, concrete virtual bindings and whole code/data are independently reviewed.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
struct Vector {
    float x, y, z, w;
};
struct Matrix {
    struct Vector rows[4];
}
__attribute__((aligned(16)));
struct Method {
    short adjustment;
    short reserved;
    const struct Matrix *(*call)(void *receiver);
};
struct Object {
    char prefix[12];
    const struct Method *methods;
};
typedef int QWORD __attribute__((mode(TI)));
struct PositionOwner {
    char prefix[0x260];
    QWORD position;
};
// This VU vsub writes MAC/status flags. The compiler backend tracks the
// explicit VF input/output operands only; these flags are not exposed as
// C values or modeled clobbers. The operation preserves the original effects.
static inline QWORD SubtractVector(QWORD first, QWORD second) {
    QWORD result;
    __asm__ volatile ("vsub.xyzw %0, %1, %2" : "=j"(result) : "j"(first), "j"(second));
    return result;
}
void func_00249588(struct Object *p, const struct PositionOwner *owner, QWORD *destination) {
    if (destination) {
        const struct Method *method = &p->methods[36];
        const struct Matrix *basis = method->call((char *)p + method->adjustment);
        *destination = SubtractVector(*(const QWORD *)&basis->rows[3], owner->position);
    }
}
