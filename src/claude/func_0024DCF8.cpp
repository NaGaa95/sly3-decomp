// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); }
};
struct VEC { float x, y, z, w; };
struct OWNER { char pad[0xA4]; int nA4; };
struct VAL { int n0; qword *p4; };
struct G {
    OWNER *p0; char pad4[4]; float f8; char padC[0x20 - 0xC]; int n20; char pad24[0x88 - 0x24]; int n88;
    VEC *a8C; char pad90[0xA0 - 0x90]; VAL vA0; char padA8[0xC0 - 0xA8]; int nC0; char padC4[0xD0 - 0xC4];
};
struct SO {
    char pad[0x28]; unsigned long grf28; char pad30[0x50 - 0x30]; void *p50; char pad54[0xD0 - 0x54];
    int cD0; G *aD4; char padD8[0x220 - 0xD8]; float f220; qword *p224; qword *p228; VEC *p22C;
    char pad230[0x250 - 0x230]; qword q250; char pad260[0x288 - 0x260]; G *p288; G *p28C;
};
extern "C" {
extern qword D_00317550;
void func_0023BA40(SO *p);
void func_0023B9C8(SO *p);
void func_002405F8(G *source, void *space, int inserted, G *dest);
void func_00240100(G *p);
float func_002407D8(void *p);
void func_0018B1E0(G *p);
void func_0024DB88(SO *p);
void func_0024DCF8(SO *p, G *src);
}
static inline int FRoom(G *g) { return g->n20 < g->n88; }
static inline float GMin(float a, float b) { return a < b ? a : b; }
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline VAL *Val(G *d)
{
    if (d->nC0 != d->p0->nA4) func_0018B1E0(d);
    return &d->vA0;
}
void func_0024DCF8(SO *p, G *src)
{
    G *d;
    int i, off, fExtra;
    if ((int)(p->grf28 >> 56) & 1) func_0023BA40(p);
    {
        register int base asm("$3") = (int)p->aD4; /* pin: array base in v1 as in the target */
        d = (G *)(base + p->cD0++ * (int)sizeof(G));
    }
    p->p288 = d;
    fExtra = !FRoom(src);
    func_002405F8(src, p->p50, fExtra ? 3 : 2, d);
    func_00240100(p->p288);
    p->f220 = 3.40282346638528859812e+38f;
    for (i = 0; i < p->p288->n20; i++)
        p->f220 = GMin(p->f220, p->p288->a8C[i].z);
    d = p->p288;
    off = d->n20 * 16;
    d->n20 += 2;
    *(qword *)(off + (int)p->p288->a8C) = p->q250;
    {
        qword *pd = (qword *)(off + (int)p->p288->a8C + 16);
        *pd = AddScaled(p->q250, D_00317550, VU_FLOAT(-50.0f));
    }
    p->p288->f8 = func_002407D8(&p->p288->n88);
    p->p288->nC0 = -1;
    p->p28C = src;
    {
        VAL *v = Val(p->p288);
        p->p224 = (qword *)((char *)v->p4 + off);
        p->p228 = (qword *)((char *)v->p4 + (off + 16));
    }
    if ((int)(p->grf28 >> 56) & 1) func_0023B9C8(p);
    if (fExtra) p->p22C = &p->p288->a8C[p->p288->n20];
    func_0024DB88(p);
}
