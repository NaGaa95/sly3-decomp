// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct ColorBytes { unsigned char r, g, b, a; };
struct Color {
    unsigned char r, g, b, a;
    Color(const Color &c) { *(ColorBytes *)this = *(const ColorBytes *)&c; }
} __attribute__((aligned(16)));
struct Matrix2D { float a[6]; } __attribute__((aligned(16)));
struct FrameSlot { char pad[8]; short savedFrame; short subframe; float time; int active; void *sound; };
struct Frame { char pad[0x14]; };
struct FrameOwner { int x0; Frame *frames; FrameSlot *slots; char padc[0x20]; Matrix2D *matrix; };
static inline Matrix2D Mul(const Matrix2D &q, const Matrix2D &n)
{
    float m0 = q.a[0], m1 = q.a[1], m2 = q.a[2], m3 = q.a[3], m4 = q.a[4], m5 = q.a[5];
    Matrix2D r;
    r.a[0] = m0 * n.a[0] + m1 * n.a[2];
    r.a[1] = m0 * n.a[1] + m1 * n.a[3];
    r.a[2] = m2 * n.a[0] + m3 * n.a[2];
    r.a[3] = m2 * n.a[1] + m3 * n.a[3];
    r.a[4] = m4 * n.a[0] + m5 * n.a[2] + n.a[4];
    r.a[5] = m4 * n.a[1] + m5 * n.a[3] + n.a[5];
    return r;
}
extern "C" void func_00269418(float,Frame *pf, int z, Matrix2D *matrix, Color c0, Color c1);
extern "C" void func_00267110(FrameOwner *p, int i, int z, Matrix2D *matrix, float t, Color c0, Color c1)
{
    FrameSlot *e = &p->slots[z];
    Matrix2D m;
    e->savedFrame = i;
    e->active = 0;
    e->time = t;
    e->subframe = 0;
    Matrix2D *pmUse;
    if (p->matrix) {
        m = Mul(*matrix, *p->matrix);
        pmUse = &m;
    } else {
        pmUse = matrix;
    }
    func_00269418(t, &p->frames[e->savedFrame], z, pmUse, c0, c1);
}
