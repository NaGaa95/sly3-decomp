// Set the original three-row basis, query the resulting matrix and explicitly update the receiver's heading.
// Complete original inputs, concrete virtual bindings and whole code/data are independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct Vector {
    float x, y, z, w;
};
struct Matrix3 {
    struct Vector rows[3];
}
__attribute__((aligned(16)));
struct Matrix4 {
    struct Vector rows[4];
}
__attribute__((aligned(16)));
struct Method {
    short adjustment, reserved;
    const struct Matrix4 *(*call)(void *receiver);
};
struct Receiver {
    char prefix[12];
    const struct Method *methods;
};
void func_0023D338(void *receiver, const struct Matrix3 *source);
float func_002A3EE8(float y, float x);
void func_0024E878(void *receiver, float angle);
void func_0024E3A8(struct Receiver *p, const struct Matrix3 *source) {
    const struct Method *method;
    const struct Matrix4 *basis;
    func_0023D338(p, source);
    method = &p->methods[36];
    basis = method->call((char *)p + method->adjustment);
    func_0024E878(p, func_002A3EE8(basis->rows[0].y, basis->rows[0].x));
}
