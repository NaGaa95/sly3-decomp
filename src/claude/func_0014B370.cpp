// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// func_0014B370 (A46): A12 draft fixed: CTX must have a non-BLK mode (qword member) so it does not reuse the M4 temp slot (ctx at 0x40); Pos() reads p->p8 after the VECTOR copy; SetPos(&p->m, v) inline.
typedef int qword __attribute__((mode(TI)));
struct ALLOCREQ { int cb; int cbAlign; ALLOCREQ(int b, int a) { cb = b; cbAlign = a; } };
class CTX {
    qword q;
public:
    CTX() __asm__("__3CTX");
    ~CTX() __asm__("_$_3CTX");
};
struct M4 { qword r[4]; };
union U4 { M4 m; float f[4][4]; };
struct VTE { short d; short pad; M4 *(*pfn)(void *); };
struct VT { char pad[0x120]; VTE e120; };
struct LO { char pad[0xC]; VT *pvt; };
struct VECTOR { union { qword q; float f[4]; }; VECTOR(const VECTOR &v) __asm__("func_002BC400"); };
struct ENT { VECTOR pos; char pad10[0x50 - 0x10]; };
struct P {
    float g0; LO *plo; void *p8; char padC[0x14 - 0xC]; float g14; int c18; char pad1C[0xA4 - 0x1C]; void *pA4; ENT *aent;
    char padAC[0xE0 - 0xAC]; qword qE0; U4 m;
};
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
extern "C" {
extern struct CLOCK { float t; } g_clock;
void *PvAllocSlot(ALLOCREQ *req) __asm__("PvAllocSlot__FP8ALLOCREQ");
qword func_00289D68(void *p, ENT *pe);
qword *func_002BA818(qword *out, qword v);
void func_0014B248(P *p, M4 *pm);
void func_0014B9F8(int n, qword *aq, void *p, U4 *pm);
void func_0014B370(P *p);
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(VU_VECTOR a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a.q), "j"(b)); return r; }
static inline float Dot(qword a, qword b)
{
    qword r, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(r), "=&j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r));
    return g;
}
static inline void Check(P *p, M4 m)
{
    qword d = Sub(m.r[3], p->qE0);
    int f = p->g14 * p->g14 < Dot(d, d);
    if (f)
        func_0014B248(p, &m);
}
static inline qword Pos(P *p, ENT *pe) { return Add(VECTOR(pe->pos).q, func_00289D68(p->p8, pe)); }
static inline void SetPos(U4 *pm, qword v) { func_002BA818(&pm->m.r[3], v); pm->f[3][3] = 1.0f; }

void func_0014B370(P *p)
{
    if (g_clock.t == p->g0)
        return;
    p->g0 = g_clock.t;
    if (p->g14 >= 0.0f)
        Check(p, *p->plo->pvt->e120.pfn((char *)p->plo + p->plo->pvt->e120.d));
    if (p->c18 == 1) {
        SetPos(&p->m, Pos(p, p->aent));
    } else {
        CTX ctx;
        int i;
        qword *aq = (qword *)PvAllocSlot(&ALLOCREQ(p->c18 * 16, 16));
        for (i = 0; i < p->c18; i++) {
            ENT *pe = &p->aent[i];
            ((int *)pe)[3] = -1;
            aq[i] = Pos(p, pe);
        }
        func_0014B9F8(p->c18, aq, p->pA4, &p->m);
    }
}
