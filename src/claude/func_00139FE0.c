// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M { short delta, pad; void *fn; };
struct LM { float gMin, gMax; };
struct T { char pad[0x30]; qword pos; };
struct CVT { char pad[0x8]; struct M m8; struct M m10; };
struct C { char pad[0x2C]; struct CVT *vt; };
struct PVT { char pad[0x120]; struct M m120; char pad1[0x388 - 0x128]; struct M m388; };
struct Q { char pad[0x50]; int x50; char pad1[0x5C - 0x54]; struct P *p5C; };
struct P { char pad[0xC]; struct PVT *vt; char pad1[0x134 - 0x10]; struct C *pc; char pad2[0x29C - 0x138]; char a29C[0x11B4 - 0x29C];
    struct P *p11B4; };
int func_0013B500(struct P *p, int n);
int func_0011EE30(const struct LM *plm, float g);
struct Q *func_002387A8(void *p, int n);
void func_001ADDD0(struct P *p, int n, int m);
void func_00139FC0(struct P *p);
static const struct LM s_lm = { 250.0f, 1000.0f };
static inline int CTest(struct C *c, int n, float g) { struct M *m = &c->vt->m8; return ((int (*)(void *, int, float))m->fn)((char *)c + m->delta, n, g); }
static inline void CSet(struct C *c, int n) { struct M *m = &c->vt->m10; ((void (*)(void *, int))m->fn)((char *)c + m->delta, n); }
static inline int PTest(struct P *p, int n) { struct M *m = &p->vt->m388; return ((int (*)(void *, int))m->fn)((char *)p + m->delta, n); }
static inline struct T *PXf(struct P *p) { struct M *m = &p->vt->m120; return ((struct T *(*)(void *))m->fn)((char *)p + m->delta); }
static inline float Y(qword q) { float f; __asm__("pextuw %0, $0, %1" : "=r"(f) : "r"(q)); return f; }
void func_00139FE0(struct P *p)
{
    if (p->p11B4 && func_0013B500(p->p11B4, 0x3A) && CTest(p->pc, 0x80, 0.35f) && PTest(p, 2)) {
        struct P *pa = p->p11B4;
        qword a = PXf(pa)->pos;
        qword d, l;
        float g;
        int f;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(PXf(p)->pos));
        __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(l) : "j"(d));
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(l));
        __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
        f = 0;
        if (g < 400.0f)
            f = func_0011EE30(&s_lm, Y(d)) != 0;
        if (f) {
            struct Q *q = func_002387A8(pa->a29C, 0xDA);
            if (q && q->p5C == p && q->x50 < 2 && q->x50 >= 0) {
                func_001ADDD0(p, 0xD, -1);
                CSet(p->pc, 0x80);
                return;
            }
        }
    }
    func_00139FC0(p);
}
