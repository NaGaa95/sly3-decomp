// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001672A0: Sly 3 version of Sly 2 func_0014EDA0 (src/hand) -- collision push-out solve over a list of objects.
typedef int qword __attribute__((mode(TI)));
struct X { qword pos; qword normal; qword x20; };
struct E { int a, b, c; };
struct LOV { char pad[0xA4]; int xA4; };
struct ES { int a, b; int c; struct E *ae; };
struct LO { struct LOV *pvt; char pad[0x78 - 4]; struct ES es; char pad1[0xC0 - 0x88]; int xC0; };
static inline struct E *PeEnd(struct ES *pes) { return &pes->ae[pes->c]; }
struct AL { int cb; int cbAlign; };
struct FRAME { int a[4]; };
void func_0018B1E0(struct LO *po);
void func_001D2770(struct FRAME *p);
void func_001D2798(struct FRAME *p, int n);
void *func_001D25B0(struct AL *pal);
int func_001CD098(qword pos, struct LO *po, struct E *pe, float g, int a, int b, int cMax, struct X *ax);
void func_0011BA98(int c, float *aDot, float *aW, float *aZ, float g);
qword func_001205F0(qword v, float g);

static inline int Dot(qword *pa, qword *pb)
{
    qword nj = *pb;
    qword t = *pa;
    qword one;
    int d;
    __asm__("vmul.xyz %0, %0, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "+j"(t), "=j"(one) : "j"(nj));
    __asm__("qmfc2.ni %0, %1" : "=r"(d) : "j"(t));
    return d;
}

static inline void *PvAlloc(int cb, int cbAlign)
{
    struct AL al;
    al.cb = cb;
    al.cbAlign = cbAlign;
    return func_001D25B0(&al);
}

qword func_001672A0(void *p, int c, struct LO **apo, int grf, float (*pfn)(void *, qword, qword, struct X *),
                    qword pos, qword v, float g, float h)
{
    struct X ax[64];
    int n = 0;
    int i, j;

    {
    int k;
    for (k = 0; k < c; k++) {
        struct LO *po = apo[k];
        struct E *pe;
        struct ES *pes;
        if (po->xC0 != po->pvt->xA4)
            func_0018B1E0(po);
        pes = &po->es;
        if (grf & 1)
            pe = PeEnd(pes);
        else
            pe = (struct E *)0x7FFFFFFF;
        n += func_001CD098(pos, po, pe, g, 0, 0, 64 - n, &ax[n]);
    }
    }
    if (n == 0)
        return v;
    {
        struct FRAME frame;
        float *pg;
        qword r, sum;
        float *aDot, *aW, *aZ;
        func_001D2770(&frame);
        aDot = PvAlloc(n * n * 4, 0x10);
        aW = PvAlloc(n * 4, 0x10);
        aZ = PvAlloc(n * 4, 0x10);
        pg = aDot;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++)
                *(int *)pg++ = Dot(&ax[i].normal, &ax[j].normal);
        }
        pg = aW;
        for (i = 0; i < n; i++)
            *pg++ = pfn(p, pos, v, &ax[i]);
        func_0011BA98(n, aDot, aW, aZ, 4.0f * h);
        pg = aZ;
        __asm__("vsub.xyzw %0, $vf0, $vf0" : "=j"(sum));
        for (i = 0; i < n; i++) {
            union { qword q; float f[4]; } s;
            __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(*pg++));
            __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(sum) : "0"(sum), "j"(ax[i].normal), "j"(s.q));
        }
        r = func_001205F0(sum, h);
        {
        qword res;
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(res) : "j"(v), "j"(r));
        func_001D2798(&frame, 2);
        return res;
        }
        func_001D2798(&frame, 2);
        return r;
    }
}
