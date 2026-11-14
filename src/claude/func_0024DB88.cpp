// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0024DB88: advance the source cloud, clear its samples, and place the target point at the centroid of the other
// cloud carried from its space into the first's. Matching notes: the sum is a plain qword (its 0x90 slot is
// the reload spill across the matrix calls), g is the stack home of the 1/count VU float (declared first -> sp+0), the
// loop re-reads p->pcl1->av, the matrix product uses the comma-expression form so &m/&mInv sit in s-regs.
typedef int qword __attribute__((mode(TI)));
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
struct M4 { qword r[4]; };
struct LO { char pad[0x40]; M4 mat; };
struct SMP { int f0; void *pv; };
struct CLOUD { LO *plo; char pad4[0x10]; SMP *psmp; char pad18[0x88 - 0x18]; int c; qword *av; };
struct S { char pad0[0x22C]; qword *pvOut; char pad230[0x288 - 0x230]; CLOUD *pcl0; CLOUD *pcl1; };
extern "C" {
extern struct { float t; float dt; } g_clock;
extern qword D_00317560;
void func_002403F0(CLOUD *pcl, float dt);
void *func_00292034(void *pv, int n, int cb);
M4 *func_0011D768(M4 *pm, const M4 *pmSrc);
M4 *func_0011D558(M4 *pm, const M4 *pm0, const M4 *pm1);
}
static inline qword QwDivVu2(qword qw, qword g)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(g), "j"(qw));
    return r;
}
static inline qword QwXform(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}
extern "C" void func_0024DB88(S *p)
{
    VECTOR4 g;
    M4 m, mInv;
    qword vSum;
    if (!p->pcl0->psmp)
        return;
    func_002403F0(p->pcl0, g_clock.dt);
    p->pcl0->psmp->f0 = 1;
    func_00292034(p->pcl0->psmp->pv, 0, p->pcl0->c * 16);
    if (!p->pvOut)
        return;
    CLOUD *pcl = p->pcl1;
    int c = pcl->c;
    vSum = D_00317560;
    if (c > 0) {
        for (int i = 0; i < c; i++) {
            qword q;
            __asm__("vadd.xyzw %0, %1, %2" : "=j"(q) : "j"(vSum), "j"(p->pcl1->av[i]));
            vSum = q;
        }
        {
            register qword t asm("vf1"); /* pin: count in vf1 as in the target */
            __asm__("qmtc2.ni %1, %0" : "=j"(t) : "r"((float)c));
            *(qword *)&g = t;
        }
        vSum = QwDivVu2(vSum, *(qword *)&g);
    }
    func_0011D558(&m, (func_0011D768(&mInv, &p->pcl0->plo->mat), &mInv), &p->pcl1->plo->mat);
    *p->pvOut = QwXform(m, vSum);
}
