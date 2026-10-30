// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Port of Sly 2 src/hand/func_0017E0E0.cpp (heading via func_001205C8, literal radius, positions via vtable).
typedef int qword __attribute__((mode(TI)));
struct X;
extern "C" {
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
/* rodata at 0x00321820 (not in symbol_addrs): probe angle offsets */
extern const float D_00321820[16] = { 0.0f, 0.15f, -0.15f, 0.3f, -0.3f, 0.6f, -0.6f, 1.0f, -1.0f, 1.5f, -1.5f, 2.0f, -2.0f, 2.5f, -2.5f, 3.14f };
struct VTE { short d; short pad; void *pfn; };
struct X { qword a; qword v; X(); };
struct T { char pad[0x40]; struct X x40; };
struct D { char pad[0x10]; void *p10; };
struct C { char pad[0xDC]; struct D *pDC; };
struct A { char pad[0xC]; struct VTE *vt; char pad1[0xD8 - 0x10]; struct C *pD8; };
struct S { char pad[0x10]; struct A *p10; int pad2; struct T *p18; char pad3[0x1C]; struct A *p38; float f3C; };
float func_001205C8(qword v);
qword func_001EE788(struct X *s, qword v);
qword func_0011FD70(float a, float b, float c);
int func_001ED460(void *q, qword v, qword *out);
void func_002B8750(struct X *x);
void func_001D7FD0(void *p, struct X *x);
void func_0017FCF0(struct S *p);
}
inline X::X() { func_002B8750(this); }
static inline qword GETPOS(struct A *o) { return *(qword *)((char *)((void *(*)(void *))o->vt[36].pfn)((char *)o + o->vt[36].d) + 0x30); }
void func_0017FCF0(struct S *p) {
    union { qword q; } hit;
    qword a, b, d, r;
    struct T *t;
    struct C *c;
    struct D *dd;
    void *q;
    float ang, best;
    unsigned int i;
    p->f3C = g_clock.t;
    t = p->p18;
    a = GETPOS(p->p38);
    b = GETPOS(p->p10);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(b), "j"(a));
    c = p->p10->pD8;
    dd = c ? c->pDC : 0;
    q = dd ? dd->p10 : 0;
    best = 0.0f;
    ang = func_001205C8(d);
    r = func_001EE788(&t->x40, b);
    for (i = 0; i < 16; i++) {
        qword o = func_0011FD70(ang + D_00321820[i], 500.0f, 0.0f);
        qword s;
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(s) : "j"(b), "j"(o));
        if (func_001ED460(q, s, &hit.q)) {
            qword e, l;
            float g;
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(e) : "j"(hit.q), "j"(a));
            __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(e) : "j"(e));
            __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(e));
            __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
            if (g > best) {
                best = g;
                r = hit.q;
            }
        }
    }
    struct X x;
    x.v = r;
    func_001D7FD0(t, &x);
}
