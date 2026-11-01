// SLY3_AS: gnu-2.9
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Switches the controller to state n (same routine as Sly 2 func_0017D450): drops the held effect handle when leaving the
// 0..2 states, stamps the change time and creates/updates the effect that belongs to the new state.
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern struct CLOCK D_0036BB98;
struct VTE { short d; short pad; void (*pfn)(void *); };
struct O {
    char pad[0xC]; struct VTE *vt; char pad10[0x30 - 0x10];
    union { int n30; qword v30; struct { int a, b, n38; } s; } u30;
    qword v40;
    char pad50[0xA0 - 0x50];
    int nA0;
    char padA4[0xB0 - 0xA4];
    int nB0;
    int padB4;
    int nB8;
};
struct A { char pad[0x1144]; int n1144; };
struct S {
    char pad[0x10]; struct A *p10; int pad14; struct O *p18; char pad3[0x30 - 0x1C]; int n30; float f34;
    char pad4[0x88 - 0x38]; int n88; int n8C; int n90; int n94; char pad98[4]; int n9C; int nA0;
};
void func_00238AE8(void *p);
struct O *func_00238690(void *p, int n);
void func_001D8B40(struct O *o, void *args);
static inline void Notify(struct O *o) { struct VTE *e = &o->vt[8]; e->pfn((char *)o + e->d); }
void func_001D77E0(struct S *p, int n, void *args)
{
    if (n == p->n30) return;
    if (!((unsigned)n < 3 && p->n30 >= 0 && p->n30 < 3)) func_00238AE8(&p->p18);
    p->n30 = n;
    p->f34 = D_0036BB98.t;
    switch (n) {
    case 4: {
        struct O *o = func_00238690((char *)p->p10 + 0x29C, 0xCA);
        o->u30.s.n38 = p->n88;
        Notify(o);
        break;
    }
    case 3: {
        struct O *o = func_00238690((char *)p->p10 + 0x29C, 0xE4);
        o->u30.n30 = p->n9C;
        Notify(o);
        break;
    }
    case 1:
    case 2: {
        struct O *o = p->p18;
        if (o == 0) {
            o = func_00238690((char *)p->p10 + 0x29C, 0xF0);
            o->nB8 = p->n88;
            o->u30.s.n38 = p->nA0;
            if (!p->n88 || p->n8C || !(p->p10->n1144 & 4)) o->nB0 = 0xE; else o->nB0 = 0xD;
            func_001D8B40(o, args);
            Notify(o);
        } else {
            func_001D8B40(o, args);
        }
        if (p->n94) {
            if (p->n30 == 1) o->nA0 = p->n30; else o->nA0 = 0;
        } else {
            o->nA0 = 0;
        }
        break;
    }
    case -1:
    case 0:
        break;
    case 5: {
        struct O *o = func_00238690((char *)p->p10 + 0x29C, 0xE5);
        o->u30.v30 = *(qword *)args;
        o->v40 = *(qword *)((char *)args + 0x10);
        Notify(o);
        break;
    }
    }
}
