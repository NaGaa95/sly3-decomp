// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; VTE e120; char pad2[0x130 - 0x128]; VTE e130; char pad3[0x140 - 0x138]; VTE e140; };
struct PO {
    char pad[0xC]; VT *pvt; char pad1[0x1A0 - 0x10]; qword v1A0; qword pad1B0; qword mat[3];
    char pad2[0x113C - 0x1F0]; int x113C; int x1140;
};
struct OVT { char pad[0x18]; VTE e18; };
struct OBJ { OVT *pvt; };
struct ASEG { int x0; OBJ *pobj; };
struct ANIM { char pad[0x68]; float g68; };
struct S { qword q0; PO *po; int st; float t18; int x1C; ANIM *a20; ANIM *a24; };
extern "C" {
extern struct CLOCK { float t; } g_clock;
qword func_001407E8(S *);
int func_001407B8(S *);
void func_0024E8E8(PO *, qword);
ASEG *func_00136EE0(ANIM *, PO *, int, int);
void func_0023AC58(void *);
void func_00137588(ANIM *, PO *, int, void *, float, float);
}
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
/* qmtc2 form: the value goes straight to a VF register and its home slot is stored afterwards (Sly 2 func_00140F90 style) */
struct VU_FLOAT2 { qword q; VU_FLOAT2(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
/* "=rj" form (A12): the GPR value is spilled across the call and reloaded with lqc2 */
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=rj"(q) : "f"(f)); } };
static inline M4 *Matrix(PO *p) { VTE *e = &p->pvt->e120; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
static inline qword Vel(PO *p) { VTE *e = &p->pvt->e130; return ((qword (*)(void *))e->pfn)((char *)p + e->d); }
static inline void SetVel(PO *p, qword v) { VTE *e = &p->pvt->e140; ((void (*)(void *, qword))e->pfn)((char *)p + e->d, v); }
static inline qword Scale2(VU_FLOAT2 s, qword a) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s.q)); return r; }
static inline qword Scale(VU_FLOAT s, qword a) { qword r; __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(s.q), "j"(a)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Xform(const qword *m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r) : "j"(m[0]), "j"(m[1]), "j"(m[2]), "j"(v));
    return r;
}

extern "C" void func_00140CD0(S *ps, int st)
{
    ANIM *anim;
    if (st == ps->st)
        return;
    if (ps->st == -1)
        ps->q0 = func_001407E8(ps);
    ps->st = st;
    ps->t18 = g_clock.t;
    anim = 0;
    switch (st) {
    case -1:
        SetVel(ps->po, Scale(VU_FLOAT(0.5f), Vel(ps->po)));
        return;
    case 0:
    case 1: {
        anim = st == 0 ? ps->a20 : ps->a24;
        qword q = func_001407E8(ps);
        func_0024E8E8(ps->po, Sub(q, Matrix(ps->po)->r[3]));
        ASEG *seg = func_00136EE0(anim, ps->po, 1, 1);
        float r = anim->g68;
        if (!func_001407B8(ps))
            r *= 0.8f;
        OBJ *o = seg->pobj;
        VECTOR v;
        ((void (*)(void *, int, float, float, VECTOR *))o->pvt->e18.pfn)((char *)o + o->pvt->e18.d, 0, 0.0f, r, &v);
        qword nv = Xform(ps->po->mat, *(qword *)&v);
        SetVel(ps->po, nv);
        ps->po->v1A0 = Scale2(VU_FLOAT2(-1.0f), *(qword *)&v);
        ps->x1C = st;
        break;
    }
    }
    func_0023AC58(&ps->po->x1140);
    func_00137588(anim, ps->po, 1, &ps->po->x113C, 0.0f, 1.0f);
}
