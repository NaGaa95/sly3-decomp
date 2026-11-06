// Ported from the Sly 2 source src/hand/func_001FB0C0.c.
typedef int qword __attribute__((mode(TI)));
struct P { char pad[0x1C]; void *p1C; qword v20; char pad2[0x44 - 0x30]; int n40; char pad3[0x5A - 0x48]; short n4E; unsigned short f50; unsigned short n52; };
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
void func_00244CD0(struct P *p)
{
    int f = 0;
    int k;
    if (!p->n40) {
        f = p->n52 || (p->f50 & 1);
        f ^= 1;
    }
    if (!f) return;
    { int fA = p->n4E > 0; k = 0x1F1; if (fA) k = 0x1F3; }
    if (p->p1C || !FNear(D_00317560, p->v20))
        k |= 0x200;
    func_00245320(p, k, k);
}
