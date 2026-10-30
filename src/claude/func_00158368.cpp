// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Port of Sly 2 src/hand/func_001457A8.cpp (Sly 3 offsets; positions through the vtable matrix). */
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
struct O;
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; VTE e120; char pad2[0x130 - 0x128]; VTE e130; };
struct O { char pad[0xC]; VT *pvt; char pad1[0x1A0 - 0x10]; qword q1A0; char pad2[0x1BC - 0x1B0]; float g1BC; };
struct E;
struct D { char pad[0x10]; E *pe; };
struct C { char pad[0xDC]; D *pd; };
struct A { char pad[0xC]; VT *pvt; char pad1[0xD8 - 0x10]; C *pc; };
struct P {
    char pad[0x10]; A *pa; char pad1[4]; void *p18; char pad2[0x30 - 0x1C]; O *po; char pad3[0x40 - 0x34];
    qword q40; qword q50; char pad4[0x68 - 0x60]; float g68;
};
extern "C" {
extern qword D_00317550;
M3 func_0011C8C0(qword axis, float g);
int func_0013B500(void *p, int k);
E *func_00158648(P *p);
void *func_001EF038(qword a, qword b, E *pe);
void func_001D8B40(void *p, void *q);
void func_00158368(P *p);
}
struct VU_FLOAT { qword q; VU_FLOAT(const VU_FLOAT &s) { q = s.q; } VU_FLOAT(float f) { qword t; __asm__("qmtc2.ni %1, %0" : "=j"(t) : "r"(f)); q = t; } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
struct VU_FLOATM { qword q; VU_FLOATM(const float &f) { __asm__("lw %0, %1" : "=r"(q) : "m"(f)); } };

static inline M4 *Mat(O *po) { return ((M4 *(*)(void *))po->pvt->e120.pfn)((char *)po + po->pvt->e120.d); }
static inline M4 *MatA(A *pa) { return ((M4 *(*)(void *))pa->pvt->e120.pfn)((char *)pa + pa->pvt->e120.d); }

static inline qword AddScaled(VU_VECTOR a, VU_FLOATM s, VU_VECTOR b)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %3, %2x" : "=j"(r) : "j"(a.q), "j"(s.q), "j"(b.q), "j"(s.q)); /* repeated "j"(s.q): allocation-only operand */
    return r;
}

static inline qword AddScaled(VU_VECTOR a, VU_FLOAT s, VU_VECTOR b)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %3, %2x" : "=j"(r) : "j"(a.q), "j"(s.q), "j"(b.q));
    return r;
}

static inline qword MulM3(const M3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(r) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return r;
}

static inline qword Add(qword a, qword b)
{
    qword r;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}

void func_00158368(P *p)
{
    union { M4 m4; struct { M3 m; qword pos; } s; } u;
    p->q50 = Mat(p->po)->r[3];
    if (func_0013B500(p->po, 0x32)) {
        O *po = p->po;
        u.s.m = func_0011C8C0(D_00317550, po->g1BC);
        u.s.pos = AddScaled(p->q50, VU_FLOAT(-p->g68), MulM3(u.s.m, po->q1A0));
    } else {
        O *po;
        u.s.m = *(M3 *)Mat(p->po);
        po = p->po;
        u.s.pos = AddScaled(p->q50, VU_FLOATM(p->g68), ((qword (*)(void *))po->pvt->e130.pfn)((char *)po + po->pvt->e130.d));
    }
    u.s.pos = Add(u.s.pos, MulM3(u.s.m, p->q40));
    {
        A *pa = p->pa;
        D *pd = pa->pc ? pa->pc->pd : 0;
        E *pe = pd ? pd->pe : 0;
        qword r = MatA(pa)->r[3];
        qword t = u.s.pos;
        if (pe && pe != func_00158648(p))
            t = r;
        func_001D8B40(p->p18, func_001EF038(r, t, pe));
    }
}
