// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00245AC0: start a plain sound on the IOP (cf. Sly 2 CSndPlain::StartIop), Sly 3 layout.
struct VTE { short d; short p; void (*pfn)(void *); };
struct P { char pad[0xC]; struct VTE *pvt; char pad1[0x14 - 0x10]; int n14; float f18; char pad2[0x48 - 0x1C]; float f48; char pad3[0x5C - 0x4C]; unsigned short f5C; unsigned short n5E; int n60; };
struct G { char pad[0xE8]; int nE8; };
struct S { int n0; };
struct M { int n0; int pad4; int n8; int nC; short h10; short pad12; int pad14[3]; short h20; short pad22; int pad24; int n28; int pad2C; };
extern struct G D_00474FF0;
extern char D_00475480[];
extern int D_00370AC0, D_0036B250, D_0038AE90, D_0038AE94, D_0038AE98, D_0046FF30;
struct S *func_00246E98(struct G *, int);
short func_00246EE0(struct G *, struct S *);
void func_00245320(struct P *, int, int);
void func_002453D8(struct P *);
void *memset(void *, int, int);
void func_00245960(void);
void func_00290FD0(struct M *, void (*)(void), struct P *);
void func_00290FA0(struct M *);
int func_001F4AD0(void *, int);
void func_00248F00(struct G *);

void func_00245AC0(struct P *p)
{
    struct G *pg = &D_00474FF0;
    struct S *ps = func_00246E98(pg, p->n60);
    struct M m;
    int id;
    if (!ps || !pg->nE8) {
        func_00245320(p, 0x1FFF, 0);
        return;
    }
    if (p->f5C & 2) {
        func_002453D8(p);
        return;
    }
    memset(&m, 0, 0x30);
    m.n28 = 3;
    m.n0 = pg->nE8;
    m.h10 = func_00246EE0(pg, ps);
    if (p->f5C & 0x10) {
        m.n28 |= 4;
        m.n8 = (int)(p->f48 * 1024.0f);
    }
    if (p->f5C & 0x20) {
        m.n28 |= 8;
        m.nC = p->n14;
    }
    if (p->f5C & 0x40) {
        m.n28 |= 0x10;
        m.h20 = (int)(p->f18 * 1524.0f);
    }
    if (!ps->n0) {
        id = 0;
        func_00290FA0(&m);
        func_00245320(p, 0x1FFF, 0);
        switch (p->n60) {
        case 0x6F: id = D_00370AC0; break;
        case 0x73: id = D_0036B250; break;
        case 0x15: id = D_0038AE90; break;
        case 0x94: id = D_0038AE94; break;
        case 0x95: id = D_0038AE98; break;
        case 0x93: id = D_0046FF30; break;
        }
        if (id == func_001F4AD0(D_00475480, 0))
            func_00248F00(&D_00474FF0);
    } else {
        p->n5E = 1;
        p->pvt[1].pfn((char *)p + p->pvt[1].d);
        func_00290FD0(&m, func_00245960, p);
        func_00245320(p, 0x7F, 0);
    }
}
