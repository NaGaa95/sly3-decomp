// SLY3_CFLAGS: -Os -G0
// Instance identifiers, virtual matrix returns and group layouts are recovered
// from the original callers and compatible SO tables. Names are provisional.
typedef int qword __attribute__((mode(TI)));

struct VTE { short d; short pad; void (*pf)(); };
struct MAT3 { qword a[3]; };
struct MAT4 { float m[4][4]; };
struct Y { char pad[0x24]; int x24; };
struct LO {
    char pad[0xC];
    struct VTE *vt;
    char p1[0x38 - 0x10];
    struct Y *x38;
};
struct X { qword q; struct MAT3 mat; };
struct Z { qword q; struct MAT4 mat; };
struct A { int cb; int align; };
struct R {
    int n;
    struct LO **ap;
    int x8;
    int c;
    int x10;
    unsigned int value14;
    unsigned int *values18;
    char pad[0x64 - 0x1C];
    struct X *x64;
    struct Z *x68;
};
struct G { char pad[0x462C]; int c462C; struct R *ar; };

// This helper packs two scalar16-bit indices into an integer identifier.
int func_001FA5A8(int i, int c);
void *func_001D2538(struct A *pa);
void func_0011C798(struct MAT3 *pm);
void *func_00292034(void *p, int c, int cb);

static inline struct MAT4 *Matrix(struct LO *p)
{
    return ((struct MAT4 *(*)(void *))p->vt[36].pf)((char *)p + p->vt[36].d);
}

static inline void SetIdent(struct MAT4 *pm)
{
    func_00292034(pm, 0, 0x40);
    pm->m[0][0] = pm->m[1][1] = pm->m[2][2] = pm->m[3][3] = 1.0f;
}

void func_001FB150(struct G *pg)
{
    int i, j, k;
    struct LO *plo;
    struct X *px;
    struct A a;
    for (i = 0; i < pg->c462C; i++) {
        struct R *pr = &pg->ar[i];
        if (pr->c >= pr->x8)
            continue;
        for (j = pr->c; j < pr->x8; j++) {
            int v = func_001FA5A8(i, j);
            pr->values18[j] = pr->value14;
            for (k = 0; k < pr->n; k++) {
                plo = pr->ap[j * pr->n + k];
                ((void (*)(void *, int, int))plo->vt[27].pf)((char *)plo + plo->vt[27].d, v, 1);
                plo->x38->x24 = 1;
            }
        }
        a.cb = pr->n * 64;
        a.align = 0x10;
        pr->x64 = func_001D2538(&a);
        for (k = 0; k < pr->n; k++) {
            px = &pr->x64[k];
            plo = pr->ap[pr->c * pr->n + k];
            // The original makes two real matrix-pointer calls: one for
            // translation and another for the three copied basis rows.
            px->q = *(qword *)&Matrix(plo)->m[3];
            px->mat = *(struct MAT3 *)Matrix(plo);
            func_0011C798(&px->mat);
        }
        a.cb = (pr->x8 - pr->c) * 0x50;
        a.align = 0x10;
        pr->x68 = func_001D2538(&a);
        for (j = pr->c; j < pr->x8; j++)
            SetIdent(&pr->x68[j - pr->c].mat);
    }
}
