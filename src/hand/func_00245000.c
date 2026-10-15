// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
struct P { char pad[0x1C]; int n1C; qword v; };
extern qword D_00317560;
int func_0011E9F0(float, float, float);
void func_00245320(struct P *, int, int);
static inline float X(qword q) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q)); return f; }
static inline float Y(qword q) { float f; __asm__("prot3w %0, %1" : "=r"(f) : "r"(q)); return f; }
static inline float Z(qword q) { float f; __asm__("pextuw %0, $0, %1" : "=r"(f) : "r"(q)); return f; }
static inline int FNear(qword a, qword b)
{
    return func_0011E9F0(X(a), X(b), 0.0001f) && func_0011E9F0(Y(a), Y(b), 0.0001f) && func_0011E9F0(Z(a), Z(b), 0.0001f);
}
void func_00245000(struct P *p, qword v)
{
    p->v = v;
    if (!FNear(D_00317560, v)) func_00245320(p, 0x200, 0x200);
    else if (!p->n1C) func_00245320(p, 0x200, 0);
}
