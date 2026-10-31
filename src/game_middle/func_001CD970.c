// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sphere-sphere contact test: when the two radii overlap, build the contact normal and point and
// hand them to the contact reporter (same algorithm as Sly 2 func_001A9C40).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;

struct CONTACT;
struct X { char pad[0x70]; qword pos; };
struct S { struct X *px; int x4; float r; };

extern qword D_00317550;

void func_001CB8B0(void *p, struct S *a, struct S *b, qword pos, qword dir, int k, int x, int y, struct CONTACT **out, float g);

void func_001CD970(void *p, struct S *a, struct S *b, struct CONTACT **out)
{
    qword pb, d, l, one, dir, pos, pa;
    float rsum, len2, g, r2;
    U u;
    register struct X *xb __asm__("$2") = b->px; // register pin: original loads b->px into $v0 first
    struct X *xa = a->px;

    pa = xa->pos;
    pb = xb->pos;
    rsum = a->r + b->r;
    r2 = rsum * rsum;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(pa), "j"(pb));
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(l), "=&j"(one) : "j"(d));
    __asm__ __volatile__("qmfc2.ni %0, %1" : "=r"(len2) : "j"(l));
    if (r2 < len2)
        return;
    if (len2 < 1e-4f) {
        g = 0.0f;
        dir = D_00317550;
    } else {
        qword s;
        float t;
        __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(t) : "f"(len2));
        g = t;
        __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(g));
        u.q = s;
        __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(dir) : "j"(u.q), "j"(d));
    }
    {
        qword s;
        __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(-a->r));
        u.q = s;
        __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(pos) : "j"(pa), "j"(dir), "j"(u.q));
    }
    func_001CB8B0(p, a, b, pos, dir, 7, 0, 0, out, g - rsum);
}

typedef char U_Size[sizeof(U) == 16 ? 1 : -1];
