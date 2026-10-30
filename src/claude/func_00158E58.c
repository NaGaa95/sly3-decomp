// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; void *(*call)(void *); };
struct CLOCK { float t; };
extern struct CLOCK g_clock;
struct P { unsigned char pad00[0xC]; struct Method *methods; char pad[0x360 - 0x10]; int x360; char pad2[0xE44 - 0x364];
           int xE44; char pad3[0x10D4 - 0xE48]; int x10D4; };
struct S { char pad[0x10]; struct P *x10; char pad2[0x30 - 0x14]; int state; float t; struct P *x38; };
extern qword D_00317530;
extern const float D_00320728;
extern const float D_0032072C;
void func_002389A0(struct S *s);
int func_001C8610(struct P *p);
void func_001591E8(struct S *s, int st);
#define MATRIX(o) ((struct Matrix *)(o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
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
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(d));
    return g;
}
static __inline__ float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static __inline__ float G(qword q) { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(q)); return g; }
void func_00158E58(struct S *s)
{
    qword a, l;
    qword *fb;
    U d;
    float len;
    int st;
    func_002389A0(s);
    if (s->state == -1)
        return;
    if (s->x10->xE44 != -1 || !func_001C8610(s->x38) || s->x38->x360) {
        func_001591E8(s, -1);
        return;
    }
    a = MATRIX(s->x38)->rows[3];
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d.q) : "j"(a), "j"(MATRIX(s->x10)->rows[3]));
    d.f[2] = 0.0f;
    l = Len(d.q);
    fb = &D_00317530;
    if (G(l) < 1e-4f)
        d.q = *fb;
    else
        d.q = Div(d.q, l);
    len = F(l);
    do {
        st = s->state;
        switch (st) {
        case 0:
            if (len < 350.0f) {
                if (Dot(MATRIX(s->x10)->rows[0], d.q) > 0.8f)
                    func_001591E8(s, 2);
            } else if (D_0032072C < len) {
                func_001591E8(s, 1);
            }
            break;
        case 1:
            if (len < D_00320728)
                func_001591E8(s, 0);
            break;
        case 2:
            if (s->x10->x10D4 == -1 && g_clock.t - s->t > 0.1f)
                func_001591E8(s, -1);
            break;
        }
    } while (s->state != st);
}

/* Read-only tuning values (defined after the function so the loads are not folded). */
const float D_00320728 = 250.0f;
const float D_0032072C = 350.0f;
