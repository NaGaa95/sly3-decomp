// Return the original matrix heading relative to the actual reference heading, normalized to the original angle range.
// Complete original inputs, concrete virtual bindings and whole code/data are independently reviewed.
// SLY3_CFLAGS: -Os -G0
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
float func_002A3EE8(float y, float x);
float func_0011E3B8(float angle);
extern float D_0047A2C8;
float func_00219000(struct Object *p) {
    const struct Method *method = &p->methods[36];
    const struct Matrix *basis = method->call((char *)p + method->adjustment);
    float angle = func_002A3EE8(basis->rows[0].y, basis->rows[0].x);
    return func_0011E3B8(angle - (D_0047A2C8 + 3.1415927410125732421875f));
}
