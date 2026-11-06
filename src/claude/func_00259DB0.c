// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VE { short d; short pad; void *pf; };
struct XF { char pad[0x30]; qword pos; };
struct LO { char pad[0xC]; struct VE *vt; };
struct X { char pad[0xC]; struct VE *vt; char pad2[0x160 - 0x10]; void *p160; };
struct S { struct LO *po; int k; float t; struct X *x; int n; };
extern struct { float t; float dt; } g_clock;
void func_00259F88(struct S *p, int k);

void func_00259DB0(struct S *p)
{
    int k;
    if (!p->n)
        return;
    do {
        k = p->k;
        switch (k) {
        case 0: {
            struct X *x = p->x;
            int f;
            struct VE *pe;
            void *pthis;
            if (!x)
                break;
            f = 0;
            pe = &x->vt[77];
            pthis = (char *)x + pe->d;
            if (((int (*)(void *, qword))pe->pf)(pthis, ((struct XF *(*)(void *))p->po->vt[36].pf)((char *)p->po + p->po->vt[36].d)->pos)) {
                qword v = ((qword (*)(void *))p->po->vt[38].pf)((char *)p->po + p->po->vt[38].d);
                float z;
                __asm__("pextuw %0, $zero, %1" : "=r"(z) : "r"(v));
                if (z < 0.0f)
                    f = 1;
            }
            if (f)
                func_00259F88(p, 1);
            break;
        }
        case 1:
            if (!p->x)
                func_00259F88(p, 0);
            else if (g_clock.t - p->t > 0.0f &&
                     !((int (*)(void *, void *))p->po->vt[80].pf)((char *)p->po + p->po->vt[80].d, p->x->p160))
                func_00259F88(p, 2);
            break;
        case 2:
            if (!p->x || ((int (*)(void *, void *))p->po->vt[80].pf)((char *)p->po + p->po->vt[80].d, p->x->p160))
                func_00259F88(p, 0);
            break;
        }
    } while (p->k != k);
}
