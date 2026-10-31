// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta, pad; void *fn; };
struct M4 { qword r[4]; };
struct LO { char pad0[0xC]; VTE *vt; char pad10[0x310 - 0x10]; char curve[1]; };
struct VU_FLOAT {
    qword qw;
    VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=r"(qw) : "f"(f)); }
};
struct OBJ {
    LO *plo0;
    int pad4;
    int n8;
    char padC[0x1C - 0xC];
    void *pvt;
    LO *ploA;
    LO *ploB;
    char pad28[0x30 - 0x28];
    qword pos;
    float g40;
    OBJ(int a1, int a2, LO *ploA, LO *ploB) __asm__("func_0019F8B0");
};
extern "C" {
extern char D_0035A248[];
void func_00169C90(OBJ *p, int a1, int a2);
float func_0011EE68(void *curve, float u);
}
static inline qword PosOf(LO *p)
{
    VTE *e = &p->vt[36];
    return ((M4 *(*)(void *))e->fn)((char *)p + e->delta)->r[3];
}
static inline qword QwCombine(VU_FLOAT g0, qword a, VU_FLOAT g1, qword b)
{
    qword qw;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(qw) : "j"(g0.qw), "j"(a), "j"(g1.qw), "j"(b));
    return qw;
}
static inline float GZOfQw(qword qw)
{
    float z;
    __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(qw));
    return z;
}

OBJ::OBJ(int a1, int a2, LO *ploA, LO *ploB)
{
    OBJ *p = this;
    func_00169C90(p, a1, a2);
    p->n8 = 0x10;
    p->ploB = ploB;
    p->ploA = ploA;
    p->pvt = D_0035A248;
    qword *ppos = &p->pos;
    p->pos = QwCombine(VU_FLOAT(0.5f), PosOf(ploA), VU_FLOAT(0.5f), PosOf(p->ploB));
    p->g40 = GZOfQw(PosOf(p->plo0)) - ((float *)ppos)[2];
    p->g40 = func_0011EE68(ploA->curve, p->g40);
}
