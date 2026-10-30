// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Port of Sly 2 src/hand/func_0017DE50.c (target query now returns a {kind, object} pair; literal thresholds).
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern "C" {
extern struct CLOCK g_clock;
struct VTE { short d; short pad; void *pfn; };
struct X { qword a; qword v; };
struct T { char pad[0x40]; struct X x40; };
struct A { char pad[0xC]; struct VTE *vt; };
struct S { char pad[0x10]; struct A *p10; int pad2; struct T *p18; char pad3[0x14]; int n30; int pad4; struct A *p38; float f3C; float f40; };
struct OID { int kind; void *o; };
void func_002389A0(struct S *p);
int func_00238AA8(struct S *p);
int func_00238AD0(struct S *p);
int func_00254B80(struct A *p);
void func_0017FE90(struct S *p, int n);
struct OID func_00253EE8(struct A *a);
float func_00254640(struct A *a);
qword func_001EE788(struct X *s, qword v);
void func_0017FCF0(struct S *p);
void func_0017FA30(struct S *p);
}
static inline qword GETPOS(struct A *o) { return *(qword *)((char *)((void *(*)(void *))o->vt[36].pfn)((char *)o + o->vt[36].d) + 0x30); }
static __inline__ float Dist(qword a, qword b) {
    qword d;
    float f;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
void func_0017FA30(struct S *p) {
    int s;
    func_002389A0(p);
    while (s = p->n30, !func_00238AA8(p)) {
        switch (p->n30) {
        case 0:
            if (func_00238AD0(p)) func_0017FE90(p, 1);
            break;
        case 1:
            if (func_00254B80(p->p10)) {
                func_0017FE90(p, 2);
            } else {
                { float dt = g_clock.dt; p->f40 -= dt; }
                if (p->f40 <= 0.0f) {
                    struct OID oid = func_00253EE8(p->p10);
                    if (oid.kind == 3 && oid.o == p->p38) {
                        p->f40 = func_00254640(p->p10);
                    } else {
                        func_0017FE90(p, -1);
                    }
                }
            }
            break;
        case 2:
            if (!func_00254B80(p->p10)) func_0017FE90(p, 1);
            break;
        }
        if (p->n30 != s) continue;
        break;
    }
    if (p->n30 == 1) {
        struct T *t = p->p18;
        if (g_clock.t - p->f3C > 0.5f) {
        struct X *x = &t->x40;
        qword pos = GETPOS(p->p10);
        int f = 0;
        qword q = func_001EE788(x, pos);
        if (Dist(GETPOS(p->p10), q) < 150.0f) {
            f = 1;
        } else if (Dist(GETPOS(p->p10), GETPOS(p->p38)) < 300.0f) {
            f = 1;
        }
        if (f) func_0017FCF0(p);
        }
    }
}
