// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; void *(*call)(void *, ...); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
struct FRAME { unsigned char storage[0x10]; };
struct L { struct Object *x0; };
struct A { char pad[0x14]; struct L *x14; };
struct H { char pad[0x54]; int x54; };
struct G { char pad[0x47B4]; void *x47B4; };
struct S { unsigned char pad00[0xC]; struct Method *methods; char pad[0x2F - 0x10]; unsigned long flags : 8;
           char pad2[0x134 - 0x30]; float f134; char pad3[0x144 - 0x138]; int x144; int x148; int pad14C; int x150;
           char pad4[0x160 - 0x154]; qword q160; qword m170[3]; qword q1A0; qword q1B0; int pad1C0; int x1C4;
           int pad1C8; int pad1CC; int x1D0; int x1D4; int x1D8; char pad5[0x1E8 - 0x1DC]; struct A *x1E8; };
extern qword D_00317550;
extern struct G D_00475480;
void func_0014C9B8(struct S *s, qword a, qword b, int c);
void func_001D2770(struct FRAME *f) __asm__("__5FRAME");
void func_001D2798(struct FRAME *f, int n) __asm__("_$_5FRAME");
void func_0014CBB8(struct S *s, int *pn, struct Object ***plist);
void func_00240CB0(struct S *s, int a, struct Object *o, int b, int c, int d, qword p, qword v, int e);
void func_0025D940(void *g, int a, int b, void *c, void *d, float f);
int func_0013B500(void *p, int k);
struct H *func_001738C0(void *p, qword v, void *b);
#define MATRIX(o) ((struct Matrix *)(o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
#define VCALL(o, n) (o)->methods[n].call((unsigned char *)(o) + (o)->methods[n].delta
static inline qword Len(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword Div(qword v, qword l)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static __inline__ float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
void func_0014CE20(struct S *s)
{
    if (!(s->flags & 1))
        return;
    func_0014C9B8(s, MATRIX(s)->rows[3], D_00317550, 0);
    if (!s->x144) {
        struct FRAME frame;
        U k;
        int n;
        struct Object **list;
        int i;
        func_001D2770(&frame);
        func_0014CBB8(s, &n, &list);
        for (i = 0; i < n; i++) {
            struct Object *o = list[i];
            qword d, l, fb, v;
            register qword dir __asm__("vf2"); /* register pin: the normalized direction lives in vf2 on both paths */
            qword p;
            qword pos = MATRIX(o)->rows[3];
            p = s->q160;
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(pos), "j"(p));
            fb = D_00317550;
            l = Len(d);
            if (F(l) < 1e-4f)
                dir = fb;
            else
                dir = Div(d, l);
            __asm__("qmtc2.ni %1, %0" : "=j"(k.q) : "r"(500.0f));
            __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(v) : "j"(dir), "j"(k.q));
            func_00240CB0(s, 0, o, s->x1D0, s->x1D4, s->x1D8, p, v, 0);
        }
        func_001D2798(&frame, 2);
    }
    VCALL(s, 34), s->q160);
    VCALL(s, 35), s->m170);
    VCALL(s, 40), s->q1A0);
    VCALL(s, 41), s->q1B0);
    func_0025D940(&D_00475480, s->x148, -1, s, s, 1.0f);
    if (s->x1C4) {
        struct A *a = s->x1E8;
        void *b = s;
        if (a != (struct A *)s && func_0013B500(a, 0x85) && a->x14)
            b = a->x14->x0 == (struct Object *)a ? (void *)s : (void *)a->x14->x0;
        func_001738C0(D_00475480.x47B4, MATRIX(s)->rows[3], b)->x54 = 1;
    }
    VCALL(s, 9));
    s->x150 = 0;
    s->f134 = 3.402823466e+38f;
    VCALL(s, 3), 5, 0, 0, 0, 0);
}
