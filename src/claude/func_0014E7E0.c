// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; void *(*call)(void *, ...); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
struct S { unsigned char pad00[0xC]; struct Method *methods; char pad[0x1A0 - 0x10]; int x1A0; };
extern unsigned char D_00475480[];
void func_001C8168(void *s);
struct Object *func_001F4AD0(void *g, int i);
int func_0013B500(void *p, int k);
#define VCALL(o, n) ((o)->methods[n].call((unsigned char *)(o) + (o)->methods[n].delta))
static inline float Length(qword v)
{
    qword d, one, l;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
    return g;
}
void func_0014E7E0(struct S *s)
{
    int i;
    func_001C8168(s);
    if (s->x1A0)
        return;
    for (i = 0; i < 2; i++) {
        struct Object *o = func_001F4AD0(D_00475480, i);
        qword a, d;
        if (!o)
            continue;
        if (VCALL(o, 81))
            continue;
        if (!func_0013B500(o, 0x33))
            continue;
        if (!((int)VCALL(o, 106) & 0x80))
            continue;
        a = ((struct Matrix *)VCALL(s, 36))->rows[3];
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(((struct Matrix *)VCALL(o, 36))->rows[3]));
        if (Length(d) < 400.0f) {
            s->methods[55].call((unsigned char *)s + s->methods[55].delta, o);
            return;
        }
    }
}
