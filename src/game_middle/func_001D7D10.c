// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Per-frame update of the path follower (same routine as Sly 2 func_0017DA28): picks the state to enter next (1/2 by the
// target mode, 3 when the target segment is near the actor, 5 when the segment query fails) and stamps the update time.
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern struct CLOCK D_0036BB98;
struct W { int pad[0x28 / 4]; int n28; };
struct G { char pad[0x4DFC]; struct W *p4DFC; };
extern struct G D_00475480;
struct X { qword a; qword v; };
struct Q { char pad[0x50]; struct X x50; struct X x70; char pad2[0x110 - 0x90]; int n110; };
struct D { char pad[0x10]; void *p10; };
struct C { char pad[0xDC]; struct D *pDC; };
struct VTE { short d; short pad; void *pfn; };
struct A { char pad[0xC]; struct VTE *vt; char pad2[0xD8 - 0x10]; struct C *pD8; char pad3[0x1144 - 0xDC]; int n1144; };
struct S {
    char pad[0x10]; struct A *p10; char pad2[0x1C]; int n30; char pad3[0x2C]; struct X x60;
    float f80; int n84; char pad4[0x10]; int n98; struct Q *p9C; int nA0;
};
int func_00238AA8(struct S *p);
void func_001D77E0(struct S *p, int n, void *args);
void func_001D7B80(struct S *p);
void func_002B8750(struct X *x);
qword func_001EE788(struct X *s, qword v);
void func_00120A00(qword p, qword a, qword b, qword *pc, float *pt, int n);
void *func_001EF038(qword a, qword b, void *c);
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static __inline__ qword Position(struct A *o)
{
    struct VTE *e = &o->vt[36];
    return ((qword *(*)(void *))e->pfn)((char *)o + e->d)[3];
}
void func_001D7D10(struct S *p) {
    struct X x;
    int k;
    void *args;
    if (p->n30 == -1) return;
    if (!(p->p10->n1144 & 2)) return;
    if (func_00238AA8(p)) return;
    func_001D77E0(p, 0, 0);
    args = 0;
    func_001D7B80(p);
    func_002B8750(&x);
    if (p->n98 == 0) {
        x = p->x60;
        k = 1;
    } else {
        struct Q *q = p->p9C;
        x = q->x50;
        k = 2;
        if (q->n110 == 0) {
            union { qword q; float f[4]; } c;
            float t;
            qword pos = Position(p->p10);
            qword a = func_001EE788(&q->x50, pos);
            qword b = func_001EE788(&q->x70, pos);
            int f;
            func_00120A00(pos, a, b, &c.q, &t, 0);
            f = 0;
            if (t > 0.0f && t < 1.0f) {
                qword d, l;
                float g;
                __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(c.q), "j"(pos));
                __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(d));
                __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
                __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
                if (g < 50.0f) {
                    if (__builtin_fabsf(c.f[2] - GetZ(pos)) < 300.0f) f = 1;
                }
            }
            if (f) k = 3;
        }
    }
    if (k > 0) if (k < 3) {
        qword pos = Position(p->p10);
        qword q = func_001EE788(&x, pos);
        void *e;
        if (!p->nA0) {
            struct C *c = p->p10->pD8;
            struct D *d = c ? c->pDC : 0;
            e = d ? d->p10 : 0;
        } else {
            e = 0;
        }
        args = func_001EF038(pos, q, e);
    }
    func_001D77E0(p, k, args);
    p->f80 = D_0036BB98.t;
    p->n84 = D_00475480.p4DFC->n28;
}
