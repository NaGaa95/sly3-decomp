// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct LM { float gMin, gMax; };
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; struct VTE e120; };
struct D { char pad[0x10]; void *p10; };
struct C { char pad[0xDC]; struct D *pd; };
struct PO {
    char pad[0xC]; struct VT *pvt; char pad1[0xD8 - 0x10]; struct C *pc; char pad2[0x33C - 0xDC]; int x33C;
    char pad3[0x113C - 0x340]; void *p113C; char pad4[0x11C8 - 0x1140]; int x11C8;
};
struct X { char pad[0x38]; int x38; };
struct P {
    char pad[0x10]; struct PO *p10; char pad1[4]; struct X *p18; char pad2[0x30 - 0x1C]; struct PO *p30; char pad3[0x50 - 0x34];
    qword q50; int x60; char pad4[0x6C - 0x64]; float g6C; float g70; int x74; float g78; float g7C; float g80; float g84;
    char pad5[0xA0 - 0x88]; struct PO *pA0;
};
static const struct LM s_lm0 = { 0.0f, 600.0f };
static const struct LM s_lm2 = { 0.0f, 1200.0f };
void func_002389A0(struct P *p);
int func_00238AA8(struct P *p);
int func_0013B868(struct PO *p);
struct PO *func_00157BA8(struct P *p);
int func_00158548(struct P *p);
int func_0011EE30(const struct LM *plm, float g);
void func_001586C0(struct P *p, int n);
int func_00238AD0(struct P *p);
void func_00158368(struct P *p);
void func_00138B68(void *p, float g);

static __inline__ struct M4 *Matrix(struct PO *p)
{
    struct VTE *e = &p->pvt->e120;
    return ((struct M4 *(*)(void *))e->pfn)((char *)p + e->d);
}
static __inline__ float LenXY(qword d)
{
    float g;
    qword t;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(t) : "j"(d));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(t));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(t));
    return g;
}
static __inline__ qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static __inline__ float Len(qword d)
{
    qword t;
    float g;
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static __inline__ void GClamp(float *pg, float lo, float hi) { if (*pg < lo) *pg = lo; else if (hi < *pg) *pg = hi; }

void func_00157FA0(struct P *p)
{
    struct PO *po, *p30, *pso;
    qword a, b;
    float gXY, g;
    int k;
    func_002389A0(p);
    po = p->p10;
    p30 = p->p30;
    a = Matrix(po)->r[3];
    b = Matrix(p30)->r[3];
    gXY = LenXY(Sub(a, b));
    if (p->x74) {
        if (p->g70 < gXY)
            p->x74 = 0;
    } else {
        if (gXY < p->g6C)
            p->x74 = 1;
    }
    g = 3.40282347e+38f;
    switch (func_0013B868(po)) {
    case 0x34:
    case 0x35:
    case 0x36:
        if (p->x74 && po->x11C8) {
            pso = func_00157BA8(p);
            if (pso) {
                qword c = Matrix(pso)->r[3];
                float dA = Len(Sub(c, a));
                float dB = Len(Sub(c, b));
                g = dA < dB ? dA : dB;
            }
        }
        break;
    }
    while (!func_00238AA8(p)) {
        int state = p->x60;
        int f;
        switch (state) {
        case 0:
            f = func_00158548(p) != 0;
            if (f)
                func_001586C0(p, 1);
            else if (func_0011EE30(&s_lm0, g)) {
                p->pA0 = pso;
                func_001586C0(p, 2);
            }
            break;
        case 1:
            if (po->x33C == -1)
                func_001586C0(p, 0);
            break;
        case 2:
            f = func_00158548(p) != 0;
            if (f)
                func_001586C0(p, 1);
            else if (!func_0011EE30(&s_lm2, g))
                func_001586C0(p, 0);
            else if (func_00238AD0(p))
                func_001586C0(p, 0);
            break;
        }
        if (p->x60 == state)
            break;
    }
    if (p->x60 == 0) {
        struct D *pd = po->pc ? po->pc->pd : 0;
        void *pv = pd ? pd->p10 : 0;
        if (!pv)
            p->p18->x38 = 1;
        if (200.0f < LenXY(Sub(p->q50, b)))
            func_00158368(p);
        if (po->p113C) {
            float t = (gXY - p->g78) / (p->g7C - p->g78);
            GClamp(&t, 0.0f, 1.0f);
            func_00138B68(po->p113C, (1.0f - t) * p->g80 + t * p->g84);
        }
    }
}
