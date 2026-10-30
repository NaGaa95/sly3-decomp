// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; void *(*call)(void *); };
struct CLOCK { float t; };
extern struct CLOCK g_clock;
struct Scope { unsigned char unused_storage[16]; };
struct S { unsigned char pad00[0xC]; struct Method *methods; char pad[0x194 - 0x10]; int x194; int x198;
           char pad2[0x394 - 0x19C]; int state; char pad3[0x3B8 - 0x398]; struct S *x3B8; int pad3BC; void *x3C0;
           struct S *x3C4; float x3C8; char pad4[0x41C - 0x3CC]; struct S *next; };
extern struct S *D_00479BD4;
int func_0027F258(void *p, qword v);
void func_00144628(struct S *s, int n);
void func_002BC350(void *p, int n);
#define MATRIX(o) ((struct Matrix *)(o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
static inline float Distance(qword a, qword b)
{
    qword d, one, l;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "0"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
    return g;
}
void func_00144640(struct S *s)
{
    struct Scope scope;
    struct S *best = 0;
    float bestd = 3.402823466e+38f;
    struct S *p;
    int st;
    for (p = D_00479BD4; p; p = p->next) {
        float d;
        qword a;
        if (s->x3B8 == p)
            continue;
        if (p->x194 == s->x194)
            continue;
        if (p->x3B8 != s && p->x198)
            continue;
        if (s->x3C0 && !func_0027F258(s->x3C0, MATRIX(p)->rows[3]))
            continue;
        a = MATRIX(p)->rows[3];
        d = Distance(a, MATRIX(s)->rows[3]);
        if (p == s->x3C4)
            d += -500.0f;
        if (d < bestd) {
            bestd = d;
            best = p;
        }
    }
    if (best) {
        if (!s->x3C4)
            s->x3C8 = g_clock.t;
        s->x3C4 = best;
    } else if (g_clock.t - s->x3C8 > 2.5f) {
        s->x3C4 = 0;
    }
    do {
        st = s->state;
        switch (st) {
        case 0:
            if (s->x3B8)
                func_00144628(s, 1);
            break;
        case 1:
            if (s->x3C4 && g_clock.t - s->x3C8 > 1.0f)
                func_00144628(s, 2);
            break;
        case 2:
            if (!s->x3C4) {
                if (s->x3B8)
                    func_00144628(s, 1);
                else
                    func_00144628(s, 0);
            }
            break;
        }
    } while (st != s->state);
    func_002BC350(&scope, 2);
}
