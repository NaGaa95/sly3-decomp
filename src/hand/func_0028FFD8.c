// Refresh all four cached matrix rows when the parent generation advances or an unparented receiver is dirty.
// Complete original inputs, boundaries and initialized sections are independently reviewed.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
struct Matrix4 {
    QWORD row[4];
};
struct Parent {
    char prefix[0x40];
    struct Matrix4 matrix;
    char gap80[0x24];
    int generation;
};
struct Receiver {
    char prefix[0x40];
    struct Parent *parent;
    int generation;
    char gap48[8];
    struct Matrix4 local, cached;
};
struct GlobalContext {
    char prefix[0x44F4];
    int generation;
};
extern struct GlobalContext D_00475480;
struct Matrix4 *func_0011D558(struct Matrix4 *output, const struct Matrix4 *left, const struct Matrix4 *right);
void func_0028FFD8(struct Receiver *p) {
    if (p->parent) {
        if (p->generation < p->parent->generation) {
            struct Matrix4 result;
            p->generation = p->parent->generation;
            func_0011D558(&result, &p->parent->matrix, &p->local);
            p->cached = result;
        }
    }
    else if (p->generation < 0) {
        p->generation = ++D_00475480.generation;
        p->cached = p->local;
    }
}
