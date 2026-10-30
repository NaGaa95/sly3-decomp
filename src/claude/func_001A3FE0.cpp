// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Adapted from the Sly 2 decomp (func_00175D00).
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
struct G;
struct VTE { short d; short pad; void *pfn; };
struct FL { unsigned long low : 56; unsigned long bits : 8; };
struct T {
    char pad[0xC]; struct VTE *vt; char pad2[0x18]; unsigned long fl28; char pad3[0x33C - 0x30]; int n33C;
    char pad4[0x508 - 0x340]; int n508; int n50C; char pad5[0x1014 - 0x510]; int n1014; char pad6[0x19E0 - 0x1018]; int n19E0;
};
struct A { char pad[0xC]; struct VTE *vt; char pad1[0xDC - 0x10]; int nDC; char pad2[0x107C - 0xE0]; int n107C; char pad3[0x10B4 - 0x1080]; char a10B4[8]; char a10BC[8]; char a10C4[8]; char pad4[0x1144 - 0x10CC]; int n1144; };
struct S { char pad[0x10]; struct A *p10; char pad2[0x1C]; struct T *p30; int n34; float f38; int n3C; };
struct CTX { int a[4]; };
extern "C++" {
void ConstructCtx(struct CTX *x) __asm__("__3CTX");
void DestructCtx(struct CTX *x, int flags) __asm__("_$_3CTX");
}
struct Y { char pad[0x60]; };
struct R2 { struct T *p0; };
struct R1 { char pad[0x14]; struct R2 *p14; };
struct R { int pad; struct R1 *p4; };
extern "C" {
extern struct CLOCK g_clock;
extern struct G D_00475480;
int func_0013B500(struct T *t, int n);
float atan2f(float y, float x);
void func_00120BA8(qword v, float *a, float *b, float *c);
int func_0011EE30(void *p, float f);
float func_0011E3B8(float f);
void func_00120528(qword v, int n, float *pf);
int func_0025CE90(void);
void func_0025CF18(struct G *g, qword a, qword b, int (*fn)(void), int z, int *pa, int *pb);
struct R *func_00165000(int n, qword a, qword b, int c, int d, struct Y *y);
}
static inline qword *Matrix(void *o)
{
    struct VTE *e = &((struct A *)o)->vt[36];
    return ((qword *(*)(void *))e->pfn)((char *)o + e->d);
}
static inline qword Position(void *o) { return Matrix(o)[3]; }
static inline float Yaw(struct A *a) { float *m = (float *)Matrix(a); return atan2f(m[1], m[0]); }
extern "C" int func_001A3FE0(struct S *p) {
    struct CTX x;
    struct Y y;
    float f[4];
    int na, nb;
    qword pa, pb;
    qword d;
    float g;
    int k;
    struct T *t;
    struct A *a = p->p10;
    if (!(a->n1144 & 8) || a->n107C || p->n3C || !p->p30 || ((int)(p->p30->fl28 >> 56) & 1) == 0) return 0;
    if (func_0013B500(p->p30, 0x31)) {
        struct T *q = p->p30;
        struct VTE *e = &q->vt[0x51];
        if (((int (*)(void *))e->pfn)((char *)q + e->d) == 2) return 0;
    }
    k = 0;
    if (func_0013B500(p->p30, 0x33)) {
        t = p->p30;
        if (t->n50C != -1) {
            if (t->n508 < 5) k = t->n508 >= 3;
        }
        if (t->n33C != -1) {
            if (t->n33C == 0x12) k = 1;
        }
        if (t->n1014 != -1) k = 1;
        if (func_0013B500(t, 0x34)) {
            switch (t->n19E0) {
            case 4: case 0x11:
                k = 1;
                break;
            }
        }
    }
    pa = Position(p->p10);
    pb = Position(p->p30);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(pb), "j"(pa));
    g = Yaw(p->p10);
    func_00120BA8(d, &f[0], &f[1], &f[2]);
    if (!func_0011EE30(p->p10->a10B4, f[2])) return 0;
    {
        float h = func_0011E3B8(f[0] - g);
        if (!func_0011EE30(p->p10->a10BC, h)) return 0;
    }
    func_00120528(*Matrix(p->p10), 0, &f[3]);
    {
        float h = func_0011E3B8(f[1] - f[3]);
        if (!func_0011EE30(p->p10->a10C4, h)) return 0;
    }
    if (!k) {
        if (p->n34 == 0) {
            if (g_clock.t - p->f38 < 3.0f) return 0;
        } else if (p->n34 != 2) {
            return 0;
        }
    }
    {
        struct R *r;
        ConstructCtx(&x);
        func_0025CF18(&D_00475480, pa, pb, func_0025CE90, p->p10->nDC, &na, &nb);
        r = func_00165000(0, pa, pb, na, nb, &y);
        if (r && r->p4->p14->p0 != p->p30) {
            DestructCtx(&x, 2);
            return 0;
        }
        DestructCtx(&x, 2);
        return 1;
    }
}
