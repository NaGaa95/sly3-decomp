// SLY3_ASFIX: engine-divfix1
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
extern "C" {
/* Steer the holder toward its target in the target's facing frame (states 3-6, 8, 9). */
/* C++ so `m = func_0011CBA0()` goes through a return temporary (0x40) copied to m via
   the VU rows MulT reads (single-asm MulT, result shares the vector's register); VU_FLOAT by value gives the
   shared 0x70 home slot; v enters the VU via an explicit qmtc2; len re-read through an explicit qmfc2;
   the default-vector address is taken before the branch (pd). */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
typedef struct { qword r[3]; } M3;
typedef struct { float x, y, z, w; } V4;
struct VTE { short delta; short pad; qword (*method)(void *); };
struct HOLDER { char pad[0xC]; struct VTE *vt; };
struct SELF { char pad[0x10]; struct HOLDER *p10; char pad14[0xA0 - 0x14]; qword qA0; char padB0[0xCC - 0xB0]; int xCC;
    int xD0; float gD4; };
extern struct CLOCK { float t; float dt; } g_clock;
extern qword D_00317530;
extern qword D_00317550;
M3 func_0011CBA0(qword v);
void func_00244828(struct HOLDER *, qword);
#define VCALL(po, n) ((po)->vt[n].method((char *)(po) + (po)->vt[n].delta))
static inline qword Len(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return l;
}
static inline float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline float FV(qword q) { qword t; __asm__("qmfc2.ni %0, %1" : "=r"(t) : "j"(q)); float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(t)); return g; }
static inline qword DivQ(qword v, qword l)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(v), "j"(l));
    return r;
}
static inline qword MulT(const M3 *m, qword v)
{
    qword r, a, b, c, one;
    __asm__("vmul.xyzw %2, %5, %8\n\tvmaxw.xyzw %1, $vf0, $vf0w\n\tvmul.xyzw %3, %6, %8\n\tvmul.xyzw %4, %7, %8\n\t"
            "vadday.x $ACC, %2, %2y\n\tvmaddz.x %0, %1, %2z\n\tvaddax.y $ACC, %3, %3x\n\tvmaddz.y %0, %1, %3z\n\tvaddax.z $ACC, %4, %4x\n\tvmaddy.z %0, %1, %4y"
            : "=j"(r), "=&j"(one), "=&j"(a), "=&j"(b), "=&j"(c) : "j"(m->r[0]), "j"(m->r[1]), "j"(m->r[2]), "j"(v));
    return r;
}
static inline qword Mul(const M3 *m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(r) : "j"(v), "j"(m->r[0]), "j"(m->r[1]), "j"(m->r[2]));
    return r;
}
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
static inline qword MulX(qword a, VU_FLOAT b) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(b.q)); return r; }
extern "C" {
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}

}
extern "C" int func_00133568(struct SELF *p);
int func_00133568(struct SELF *p)
{
    U v;
    qword l;
    float len, gx, gy, gdt;
    switch (p->xCC) {
    case 3:
    case 4:
    case 5:
    case 6:
    case 8:
    case 9:
        break;
    default:
        return 0;
    }
    v.q = VCALL(p->p10, 38);
    v.f[2] = 0.0f;
    const qword *pd = &D_00317530;
    qword vv;
    __asm__("qmtc2.ni %1, %0" : "=j"(vv) : "r"(v.q));
    l = Len(vv);
    if (F(l) < 1e-4f)
        v.q = *pd;
    else
        v.q = DivQ(vv, l);
    len = FV(l);
    {
        M3 m;
        m = func_0011CBA0(v.q);
        {
        V4 r, w;
        U out;
        *(qword *)&r = MulT(&m, p->qA0);
        gdt = 1.0f / g_clock.dt;
        if (p->xD0 == 1 && g_clock.t - p->gD4 < 0.15f) {
            gy = gdt;
            gx = gdt;
        } else {
            gx = 2.5f;
            if (r.x < len)
                gx = 3.5f;
            gy = 2.5f;
        }
        w.z = 0.0f;
        w.y = gy * r.y;
        w.x = gx * (r.x - len);
        *(qword *)&w = MulX(*(qword *)&w, VU_FLOAT(1.0f));
        out.q = Mul(&m, *(qword *)&w);
        v.q = VCALL(p->p10, 38);
        if (v.f[2] < -750.0f) {
            out.q = AddScaled(out.q, D_00317550, VU_FLOAT((v.f[2] - -750.0f) * -2.0f));
        }
        func_00244828(p->p10, out.q);
        }
    }
    return 1;
}
