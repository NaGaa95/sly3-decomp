// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00268438: run one sound action of a sound list (cf. Sly 2 func_002193A8; Sly 3 runs a single action, kinds 1-4).
struct VTE { short delta; short pad; int (*pfn)(void *); };
struct M { char pad[0xC]; struct VTE *vt; };
struct A { int n0; unsigned int grf; int id; int nC; };
struct E { char pad[0x14]; struct M *pm; };
struct R { char pad[8]; struct E *ae; };
struct S { int n0; struct A *aa; char pad8[4]; struct R *r; };
extern "C" {
extern char D_00474FF0[];
struct M *func_002459F8(int id);
void func_00244F08(struct M *m, int n);
void func_002BBCD8(struct M **pp, struct M *m);
void func_00244CA8(struct M *m, float g);
void func_002485D8(void *psm, int id, int a, int b);
void func_00248740(void *psm);

}
// case 2 is an inlined "stop e->pm" helper; the zero-instruction asms reproduce the copies the original
// keeps (temp -> e in a0, and the FHas load -> m in a0 before the second null test).
extern "C" void func_00268438(struct S *p, int ia, int i)
{
    struct A *a = &p->aa[ia];
    switch ((a->grf >> 25) & 7) {
    case 1: {
        struct M *m = func_002459F8(a->id);
        func_00244F08(m, 0);
        if (m->vt[8].pfn((char *)m + m->vt[8].delta) == 2)
        {
            int off = i * (int)sizeof(struct E);
            func_002BBCD8(&((struct E *)(off + (int)p->r->ae))->pm, m);
        }
        break;
    }
    case 2: {
        int off = i * (int)sizeof(struct E);
        int t = off + (int)p->r->ae;
        void *x;
        __asm__("" : "=r"(x) : "0"(t));
        __asm__("" : : "r"(t));
        if (((struct E *)x)->pm) {
            struct M **pp = &((struct E *)x)->pm;
            if (pp) {
                x = *pp;
                __asm__("" : "=r"(x) : "0"(x));
                if (x) {
                    func_00244CA8((struct M *)x, 0.0f);
                    func_002BBCD8(pp, 0);
                }
            }
        }
        break;
    }
    case 3:
        func_002485D8(D_00474FF0, a->id, 0, 0);
        break;
    case 4:
        func_00248740(D_00474FF0);
        break;
    }
}
