// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; void *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
struct CLOCK { float t; };
extern struct CLOCK g_clock;
struct T { char pad[0x40]; qword q40; int x50; };
struct E { struct Object *o; void *x4; int x8; };
struct S { unsigned char pad00[0xC]; struct Method *methods; char pad[0x198 - 0x10]; int x198;
           char pad2[0x23C - 0x19C]; void *x23C; struct T *x240; struct E e[4]; int n; int i; float f27C; float pad280;
           float f284; float f288; float f28C; int x290; };
int func_00144A90(struct S *s);
void *func_001FBE30(void *p, int n);
void func_001C8FB0(void *v, struct Object *o);
qword func_00142D20(struct S *s);
qword func_00142D98(struct S *s);
void func_00212770(struct T *t, void *v);
int func_0013B500(void *p, int k);
void func_0014D1F0(void *v, struct S *s);
void func_001FE728(void *p, int n);
int func_001F4430(struct S *s);
void func_001F4438(struct S *s, int n);
float func_0011E940(float a, float b);
#define MATRIX(o) ((struct Matrix *)(o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(d));
    return g;
}
void func_00144E40(struct S *s)
{
    if (!func_00144A90(s))
        return;
    if (s->x23C && s->x240 && s->n) {
        struct E *e = &s->e[s->i];
        struct Object *o = e->o;
        if (o) {
            void *v = func_001FBE30(s->x23C, 0);
            if (v) {
                qword a;
                func_001C8FB0(v, o);
                s->x240->x50 = 0;
                a = MATRIX(o)->rows[0];
                if (Dot(a, MATRIX((struct Object *)s)->rows[0]) > 0.0f) {
                    struct T *t = s->x240;
                    t->q40 = func_00142D20(s);
                } else {
                    struct T *t = s->x240;
                    t->q40 = func_00142D98(s);
                }
                func_00212770(s->x240, v);
                if (func_0013B500(v, 0x59))
                    func_0014D1F0(v, s);
                if (e->x4)
                    func_001FE728(e->x4, 1);
                if (!s->x198 && !s->x290)
                    func_001F4438(s, func_001F4430(s) - 1);
                s->i = (s->i + 1) % s->n;
            }
        }
    }
    s->f284 = g_clock.t + 1.0f / s->f27C;
    if (s->x198 && s->f288 < g_clock.t) {
        float t = g_clock.t;
        float k = 1.5f;
        s->f288 = t + func_0011E940(0.5f, k);
        s->f28C = s->f288 + func_0011E940(k, 2.0f);
    }
}
