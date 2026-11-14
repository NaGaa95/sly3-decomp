// SLY3_ASFIX: engine-divfix1
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00273278: push the tracked actor (p->x10, one of the two player globals) away from p->x0 in the
// ground plane (Project on D_00317550, safe-normalised, *400 + up*600) when it may be knocked back; else the 0x71 check.
// Matching notes: k = 400 is an "=rj" mfc1 VU_FLOAT (memory home 0x20), vel declared before k (slot 0x10), the
// SafeNormalize stores through a pointer in both arms; one pin (Len's qmfc2 lane register a0).
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *(*pf)(void *, ...); };
struct O { int a[3]; VTE *vt; O *x10; char pad14[0x320 - 0x14]; char x320[0x1924 - 0x320]; int x1924; char pad1928[0x19E0 - 0x1928]; int x19E0; };
struct P { O *x0; char pad4[0x8]; O *xC; O *x10; char pad14[0x148 - 0x14]; O *x148; };
extern "C" {
extern O *D_0036B250;
extern O *D_00370AC0;
extern qword D_00317530, D_00317550;
void func_0013FB20(O *, int);
void func_001B7268(void *, int, void *, void *, float);
int func_0013B500(O *, int);
void func_001C7A00(O *, int, int);
void func_002412C8(O *, float);
void func_00209428(void *);
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=rj"(q) : "f"(f)); } };
struct VU_FLOATQ { qword q; VU_FLOATQ(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
static inline qword Pos(O *o) { VTE *v = &o->vt[36]; return *(qword *)((char *)v->pf((char *)o + v->d) + 0x30); }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Project(qword v, qword n)
{
    qword d, one, r;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(v), "j"(n));
    __asm__("vmulx.xyzw %0, %1, %0x" : "+j"(d) : "j"(n));
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(v), "j"(d));
    return r;
}
static inline float Len(qword v, qword *pl)
{
    qword d, one, l;
    float f;
    register int t __asm__("$4"); // pin: the length lane goes through a0
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(f), "=&r"(t) : "j"(l));
    *pl = l;
    return f;
}
static inline qword DivQ(qword v, qword l)
{
    qword r;
    __asm__ __volatile__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static inline void SafeNormalize(qword *pv, float lf, qword l, qword v, qword def)
{
    if (lf < 0.0001f)
        *pv = def;
    else
        *pv = DivQ(v, l);
}
static inline qword Blend(qword a, const VU_FLOAT &ka, qword b, const VU_FLOATQ &kb)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(a), "j"(ka.q), "j"(b), "j"(kb.q));
    return r;
}
static inline void SetVelocity(O *o, qword v) { VTE *e = &o->vt[40]; e->pf((char *)o + e->d, v); }
extern "C" void func_00273278(P *p)
{
    O *o = p->x10;
    if (o == D_0036B250 || o == D_00370AC0) {
        qword vel;
        VU_FLOAT k(400.0f);
        qword d = Sub(Pos(o), Pos(p->x0));
        qword v = Project(d, D_00317550);
        qword l;
        float lf = Len(v, &l);
        qword dir;
        SafeNormalize(&dir, lf, l, v, D_00317530);
        vel = Blend(dir, k, D_00317550, VU_FLOATQ(600.0f));
        if (p->x10 == D_0036B250 && !p->x10->x1924) {
            func_0013FB20(p->x10, 1);
            SetVelocity(p->x10, vel);
        } else if (p->x10 == D_00370AC0 && p->x10->x19E0 == 20) {
            func_001B7268(p->x10->x320, 11, 0, 0, 1.0f);
            SetVelocity(p->x10, vel);
        }
    } else if (o->x10 == p->xC->x10) {
        if (func_0013B500(o, 0x71)) {
            VTE *e = &p->x10->vt[80];
            e->pf((char *)p->x10 + e->d, 4);
        } else {
            func_001C7A00(p->x10, 0, 15);
            func_002412C8(p->x10, 0.25f);
        }
    }
    func_00209428((char *)p->x0 + 0x940);
    if (p->x148)
        func_002412C8(p->x148, 0.25f);
}
