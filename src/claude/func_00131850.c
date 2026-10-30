// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the matched Sly 2 source src/hand/func_00174BD0.c (Sly 3 message ids, offsets and calls).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct ANIMATION;
struct G { char pad[0x3eb8]; int c; void *a[1]; };
extern struct G D_00475480;
extern void *D_0038AE90;
extern char D_0036E740[];
struct VTE { short d; short pad; void *pfn; };
struct A {
    char pad[0xC]; struct VTE *vt; char pad2[0x1A0 - 0x10]; qword v1A0; char pad3[4]; int n1B4; int n1B8; char pad4[4];
    qword m1C0[3]; char pad5[0x29C - 0x1F0]; char a29C[4];
};
struct O2 { char pad[0x14]; void *p14; };
struct O { char pad[0x30]; struct O2 *p30; };
struct S { char pad[0x10]; struct A *p10; char pad2[0x2C]; void *p40; int n44; };
struct M { struct ANIMATION *animation; float f4; int n8; };
struct ANIMATION *func_00254F80(void *p);
qword func_0024F278(struct A *a, struct ANIMATION *animation, float f);
void func_002389C0(struct S *p);
void func_00238A38(struct S *p);
struct O *func_002387A8(void *a, int n);
void *func_001F4AD0(struct G *g, int n);
void func_001A9058(void *p, int n, float f);
int func_001C8F20(void *n, void *o);
void func_00167D38(void *p, int n);
void func_00241150(struct A *a, int n);
int func_00131850(struct S *p, int msg, struct M *pm) {
    struct ANIMATION *animation;
    if (msg != 10) return 0;
    if (!p->p40) return 0;
    animation = func_00254F80(p->p40);
    if (animation != pm->animation) return 0;
    switch (pm->n8) {
    case 0x17F:
        {
            qword v = func_0024F278(p->p10, animation, pm->f4);
            qword n, r;
            U u;
            struct A *a;
            __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(-1.0f));
            __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(n) : "j"(v), "j"(u.q));
            p->p10->v1A0 = n;
            a = p->p10;
            {
                qword *m = a->m1C0;
                __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
                        : "=j"(r) : "j"(m[0]), "j"(m[1]), "j"(m[2]), "j"(v));
            }
            { struct VTE *e = &a->vt[0x28]; ((void (*)(void *, qword))e->pfn)((char *)a + e->d, r); }
        }
        return 1;
    case 0x40:
        p->p10->n1B4 = 1;
        return 1;
    case 0x41:
        p->p10->n1B4 = 0;
        return 1;
    case 0x44:
        p->p10->n1B8 = 1;
        return 1;
    case 0x46:
        p->p10->n1B8 = 2;
        return 1;
    case 0x45:
    case 0x47:
        p->p10->n1B8 = p->n44;
        return 1;
    case 0x42:
        func_002389C0(p);
        return 1;
    case 0x43:
        func_00238A38(p);
        return 1;
    case 0x4C:
        {
            struct O *o = func_002387A8(p->p10->a29C, 0xD2);
            if (o && o->p30 == func_001F4AD0(&D_00475480, 0)) func_001A9058(D_0036E740, 8, 1.0f);
        }
        return 0;
    case 0x51:
    case 0x52:
        {
            void *g = func_001F4AD0(&D_00475480, 0);
            struct O *o = func_002387A8(p->p10->a29C, 0xCD);
            if (o && func_001C8F20(o->p30->p14, g) && g == D_0038AE90) {
                switch (pm->n8) {
                case 0x52:
                    {
                        int i;
                        for (i = 0; i < D_00475480.c; i++)
                            func_00167D38(D_00475480.a[i], 0);
                    }
                    break;
                case 0x51: func_001A9058(D_0036E740, 3, 1.50000005960464477539e-01f); break;
                }
            }
        }
        return 0;
    case 0x53:
        func_00241150(p->p10, 2);
        return 0;
    }
    return 0;
}
