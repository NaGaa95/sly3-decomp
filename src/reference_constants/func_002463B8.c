// Reference algorithm: src/hand/func_001FC510.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct K { int n0; int n4; int n8; char bC; char pad[0x110 - 0xD]; };
struct X { int n0; int n4; char pad[0x34 - 8]; int n34; int n38; int n3C; char pad2[0x4C - 0x40]; int n4C; };
struct VTE { short d; short p; void (*pfn)(void *); };
struct P { char pad[0xC]; struct VTE *pvt; char pad1[0x14 - 0x10]; int n14; char pad2[0x48 - 0x18]; float f44; char pad3[0x5E - 0x4C]; short h52; char pad4[0x60 - 0x60]; struct X *p60; char pad5[0x3B8 - 0x64]; int n3B8; };
struct M { int n0; int n4; int n8; int nC; int n10; int n14; };
struct G { char pad[0x10]; int n10; };
extern struct G D_00474FF0;
void func_002BC568(struct K *);
int func_00246EF0(struct G *, struct X *);
void func_00244C28(struct P *);
void func_00245320(struct P *, int, int);
void D_00246A40(void);
void func_00291D90(int, int, int, struct M *, void (*)(void), struct P *);
static inline int FSet(struct K *pk, struct X *px)
{
    if (!px) return 0;
    {
        int a = px->n34;
        int c = px->n0;
        int d = px->n3C;
        int b = px->n4;
        pk->n8 = 2;
        pk->n4 = b ^ d;
        pk->n0 = (c ^ a) + 0xCA0;
    }
    return pk->n4 != 0;
}
void func_002463B8(struct P *p)
{
    struct K k;
    struct M m;
    int n;
    k.n8 = 2;
    func_002BC568(&k);
    n = func_00246EF0(&D_00474FF0, p->p60);
    if (FSet(&k, p->p60)) {
        if (k.n8 != 2) {
            func_00245320(p, 0x1FFF, 0);
            return;
        }
        m.n0 = k.n0;
        func_00244C28(p);
        m.n4 = (int)(p->f44 * 1024.0f);
        m.n8 = p->n14;
        m.nC = n;
        m.n10 = p->n3B8 | 1;
        {
            int fl = 0;
            if (D_00474FF0.n10 && n == 2) fl = p->p60->n4C == 0;
            m.n14 = fl;
        }
        p->h52 = 1;
        p->pvt[1].pfn((char *)p + p->pvt[1].d);
        func_00291D90(0x524B5553, 1, 0x18, &m, D_00246A40, p);
        func_00245320(p, 0x3F, 0);
    } else {
        func_00245320(p, 0x1FFF, 0);
    }
}
