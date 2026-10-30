// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the Sly 2 decomp (func_00172018, func_00172320).
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct X { qword a; qword v; };
struct Entry { short delta, pad; unsigned char *(*fn)(void *); };
struct A { int pad[3]; struct Entry *vt; char pad10[0x29C - 0x10]; char a29C[4]; };
struct S { char pad[0x10]; struct A *p10; int pad2; union { void *p18; char a18[4]; }; char pad3[0x14]; int n30; float f34; float f38; float f3C; char pad4[8]; int n48; };
void func_002389A0(struct S *p);
int func_00238AA8(struct S *p);
int func_00238AD0(struct S *p);
int func_00254B80(void *p);
int func_001A6B78(struct S *p);
qword func_001A6CA8(struct S *p);
void func_002B8750(struct X *x);
void func_001D7FD0(void *p, struct X *x);
int func_001D7F90(void *p);
void func_001A6850(struct S *p, int n);
void func_001A6A80(struct S *p);
void func_001A7500(struct S *p);
void func_0024E8E8(void *p, qword d);
struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { char pad[0xC]; struct VTE *vt; char pad2[0x2C]; int n3C; char pad3[0xA4 - 0x40]; int nA4; };
void func_00238AB8(struct S *p);
void func_00238AE8(void *p);
struct O *func_00238690(void *p, int n);
void func_001A6DF8(struct S *p);
void func_001A6B00(struct S *p, int n);
static inline qword Position(struct A *a)
{
    struct Entry *e = &a->vt[36];
    return *(qword *)(e->fn((char *)a + e->delta) + 0x30);
}
void func_001A6568(struct S *p) {
    int s;
    func_002389A0(p);
    while (!func_00238AA8(p)) {
        s = p->n30;
        switch (s) {
        case 0:
            if (func_00238AD0(p)) func_001A6850(p, 1);
            break;
        case 1:
            if (func_00254B80(p->p10)) {
                func_001A6850(p, 5);
            } else if (p->n48) {
                if (func_001A6B78(p)) {
                    func_001A6850(p, 2);
                } else {
                    qword v = func_001A6CA8(p);
                    struct X x;
                    func_002B8750(&x);
                    x.v = v;
                    func_001D7FD0(p->p18, &x);
                }
                p->n48 = 0;
            } else if (func_001A6B78(p) || func_001D7F90(p->p18)) {
                func_001A6850(p, 2);
            }
            break;
        case 2:
            if (func_00254B80(p->p10)) {
                func_001A6850(p, 5);
            } else if (p->n48) {
                if (func_001A6B78(p)) {
                    func_001A6A80(p);
                } else {
                    func_001A6850(p, 1);
                }
                p->n48 = 0;
            } else if (p->f38 < g_clock.t || func_00238AD0(p)) {
                func_001A6850(p, 4);
            } else if (g_clock.t > p->f3C) {
                func_001A6850(p, 3);
            } else {
                qword a = func_001A6CA8(p);
                qword b = Position(p->p10);
                qword d;
                __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
                func_0024E8E8(p->p10, d);
            }
            break;
        case 3:
            if (func_00254B80(p->p10)) {
                func_001A6850(p, 5);
            } else if (p->n48) {
                if (func_001A6B78(p)) {
                    func_001A6850(p, 2);
                } else {
                    func_001A6850(p, 1);
                }
                p->n48 = 0;
            } else if (p->f38 < g_clock.t) {
                func_001A6850(p, 4);
            } else {
                func_001A7500(p);
            }
            break;
        case 5:
            if (!func_00254B80(p->p10)) func_001A6850(p, 1);
            break;
        case 4:
            if (p->n48) {
                if (func_001A6B78(p)) {
                    func_001A6850(p, 2);
                } else {
                    func_001A6850(p, 1);
                }
                p->n48 = 0;
            } else if (func_00238AD0(p)) {
                func_001A6850(p, -1);
            }
            break;
        }
        if (p->n30 != s) continue;
        break;
    }
}
void func_001A6850(struct S *p, int n) {
    if (n == p->n30) return;
    func_00238AE8(p->a18);
    p->n30 = n;
    p->f34 = g_clock.t;
    switch (n) {
    case 0:
        { struct O *o = func_00238690(p->p10->a29C, 0xC9); struct VTE *e; o->n3C = 0x12; e = &o->vt[8]; e->pfn((char *)o + e->d); }
        break;
    case 1:
        {
            struct O *o = func_00238690(p->p10->a29C, 0xE1);
            struct X x;
            struct VTE *e;
            qword v;
            o->nA4 = 1;
            v = func_001A6CA8(p);
            func_002B8750(&x);
            x.v = v;
            func_001D7FD0(o, &x);
            e = &o->vt[8]; e->pfn((char *)o + e->d);
            p->f38 = 3.40282347e+38f;
        }
        break;
    case 2:
        {
            qword a = func_001A6CA8(p);
            qword b = Position(p->p10);
            qword d;
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
            func_0024E8E8(p->p10, d);
            { struct O *o = func_00238690(p->p10->a29C, 0xCA); struct VTE *e = &o->vt[8]; e->pfn((char *)o + e->d); }
            func_001A6A80(p);
        }
        break;
    case 3:
        {
            struct O *o = func_00238690(p->p10->a29C, 0xE1);
            struct VTE *e;
            o->nA4 = 1;
            func_001A6DF8(p);
            func_001A7500(p);
            e = &o->vt[8]; e->pfn((char *)o + e->d);
        }
        break;
    case 4:
        { struct O *o = func_00238690(p->p10->a29C, 0xC9); struct VTE *e; o->n3C = 0x14; e = &o->vt[8]; e->pfn((char *)o + e->d); }
        func_001A6B00(p, 0);
        p->n48 = 0;
        break;
    case 5:
        { struct O *o = func_00238690(p->p10->a29C, 0xCA); struct VTE *e; o->n3C = 1; e = &o->vt[8]; e->pfn((char *)o + e->d); }
        break;
    case -1:
        func_00238AB8(p);
        break;
    }
}
/* Next .rodata item of the original unit (a FLT_MAX literal used by a later function); it follows the jump table. */
const float D_003222EC = 3.40282347e+38f;
