// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// A18: Sly 2 func_0013AC18 counterpart, rewritten for the Sly 3 layout; scope = local with out-of-line dtor func_002BC490.
// func_00164B08 takes its float first in the prototype (arg-setup order).
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; struct VTE e120; };
struct X { char pad[0x30]; float g30; };
struct LO { char pad[0x2F]; unsigned long f : 8; char pad2[0xDC - 0x30]; struct X *px; };
struct N { char pad[0x60]; struct LO *plo; };
struct SO { char pad[0xC]; struct VT *pvt; struct SO *pparent; char pad1[0xD0 - 0x14]; struct SO *pnext; int pad2; int grfD8; struct N *pn; int xE0; };
struct E { qword v0; qword v10; int n20; struct LO *plo; int pad[2]; };
struct C { char pad[0x60]; qword q60; };
struct P { char pad[0xC]; struct VT *pvt; char pad1[0xD4 - 0x10]; struct C *pc; int pad2; struct X *px; char pad3[0x1E0 - 0xE0]; int c; struct E *ae; };
struct HIT { qword pos; qword a; qword normal; qword b; qword c; qword d; };
struct Scope { unsigned char unused_storage[16]; };
extern char D_00475480[];
extern struct { struct SO *p; } D_00479AD8;
void func_0013C388(void *pg, struct X *pa, struct X *pb, int n);
int func_00164B08(float g, qword a, qword b, qword c, int n, struct HIT *phit);
void func_002BC490(void *p, int n);
static __inline__ struct M4 *Matrix(void *pv)
{
    struct SO *p = pv;
    struct VTE *e = &p->pvt->e120;
    return ((struct M4 *(*)(void *))e->pfn)((char *)p + e->d);
}
void func_0014C218(struct P *p)
{
    struct Scope scope;
    struct HIT hit;
    int i;
    struct SO *pso;
    for (i = 0; i < p->c; i++)
        func_0013C388(D_00475480, p->px, p->ae[i].plo->px, 2);
    p->c = 0;
    for (pso = D_00479AD8.p; pso; pso = pso->pnext) {
        struct LO *plo;
        struct SO *pp;
        if (!pso->xE0)
            continue;
        if (!(pso->grfD8 & 0x100))
            continue;
        plo = 0;
        for (pp = pso->pparent; pp; pp = pp->pparent) {
            if (pp->pn) {
                plo = pp->pn->plo;
                break;
            }
        }
        if (!plo)
            continue;
        if (!(plo->f & 1))
            continue;
        {
        struct X *px;
        qword a, b, c;
        a = Matrix(pso)->r[3];
        px = plo->px;
        b = p->pc->q60;
        c = Matrix(p)->r[3];
        if (func_00164B08(px->g30, a, b, c, 1, &hit)) {
            struct E *pe;
            func_0013C388(D_00475480, p->px, plo->px, 1);
            pe = &p->ae[p->c++];
            pe->plo = plo;
            {
                qword t, vp, vn;
                int n;
                vp = hit.pos;
                pe->v0 = vp;
                vn = hit.normal;
                __asm__("vmul.xyz %2, %2, %0\n\tvaddw.x %3, $vf0, $vf0w\n\tvadday.x $ACC, %2, %2y\n\tvmaddz.x %2, %3, %2z\n\tqmfc2.ni %1, %2" : "+j"(vn), "=r"(n), "+j"(vp), "=j"(t)); /* dot(pos, normal); vn listed first as "+j" (unchanged) to get the VF numbering */
                pe->v10 = vn;
                pe->n20 = n;
            }
            if (p->c >= 4)
                break;
        }
        }
    }
    func_002BC490(&scope, 2);
}
