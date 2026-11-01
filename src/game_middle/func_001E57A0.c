// SLY3_AS: gnu-2.9
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Plays the effect list of an event entry on an actor (same routine as Sly 2 func_001BB648): each item (kind, value) either
// creates/looks up a sound object and calls one of its methods, starts a sound/effect for the actor, or plays a global effect.
typedef int qword __attribute__((mode(TI)));
typedef struct VTE { short d; short pad; void (*pfn)(); } VTE;
typedef struct SO { char pad[0xC]; VTE *vt; } SO;
typedef struct I { int k; int v; } I;
typedef struct E { int id; int n; int c; I *a; } E;
typedef struct P {
    char pad0[0xC];
    VTE *vt;
    char pad10[0x138 - 0x10];
    int x138;
    char pad13C[0x148 - 0x13C];
    int x148;
} P;
struct Registry { char pad[0x3EB8]; int count; void *items[1]; };
extern struct Registry D_00475480;
extern char D_0036E740[];
extern char D_0036BD20[];
extern char D_0036C700[];
SO *func_0017E1B8(void *g, int k, int v, P *p);
void func_0023FE38(P *p, int v);
void func_0023FEC0(P *p, int v);
void func_00240000(P *p, int v);
void func_00240080(P *p, int v);
void func_0025D940(void *g, int v, float f, int a, P *p, P *q);
void func_00167D38(void *g, int v);
void func_001A9058(void *g, int v, float f);
void func_00171E50(void *g, qword q, int v, int a, P *p);
void func_00185908(void *g, int k, int v, P *p);

static inline qword Position(void *o)
{
    VTE *e = &((SO *)o)->vt[36];
    return ((qword *(*)(void *))e->pfn)((char *)o + e->d)[3];
}

void func_001E57A0(P *p, E *pe)
{
    int i;
    SO *psPrev = 0;
    for (i = 0; i < pe->c; i++) {
        I *pi = &pe->a[i];
        SO *ps;
        if ((p->x138 > 0 || pe->n <= 0) && ((0x3F >> pi->k) & 1)) continue;
        ps = 0;
        if ((0x43 >> pi->k) & 1) {
            ps = func_0017E1B8(&D_00475480, 1, pi->v, p);
            if (!ps) continue;
        }
        switch ((unsigned int)pi->k) {
        case 6:
            psPrev = ps;
            break;
        case 0:
            ((void (*)(void *))ps->vt[8].pfn)((char *)ps + ps->vt[8].d);
            break;
        case 1:
            ((void (*)(void *))ps->vt[9].pfn)((char *)ps + ps->vt[9].d);
            break;
        case 2:
            func_0023FE38(p, pi->v);
            break;
        case 3:
            func_0023FEC0(p, pi->v);
            break;
        case 4:
            func_00240000(p, pi->v);
            break;
        case 5:
            func_00240080(p, pi->v);
            break;
        case 7:
            func_0025D940(&D_00475480, pi->v, 1.0f, -1, p, p);
            break;
        case 8:
            if (p->x148 & 2) {
                int j;
                for (j = 0; j < D_00475480.count; j++)
                    func_00167D38(D_00475480.items[j], pi->v);
            }
            break;
        case 9:
            if (p->x148 & 4) func_001A9058(D_0036E740, pi->v, 0.3f);
            break;
        case 10:
            if (p->x148 & 8) {
                qword q;
                if (psPrev) q = Position(psPrev);
                else q = Position(p);
                func_00171E50(D_0036BD20, q, pi->v, -100, p);
            }
            break;
        case 11: {
            int *apv[1];
            apv[0] = &pi->v;
            ((void (*)(void *, int, int, int, int **, int))p->vt[3].pfn)((char *)p + p->vt[3].d, 4, 0, 1, apv, 0);
            break;
        }
        case 12:
            func_00185908(D_0036C700, 1, pi->v, p);
            break;
        }
    }
}
