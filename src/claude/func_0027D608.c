// Port of Sly 2 func_00226370.
typedef int qword __attribute__((mode(TI)));
static __inline__ qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
struct S { char pad[0x4C]; int x4C; char pad2[0x19C - 0x50]; float f19C; float f1A0; char pad3[0x1DC - 0x1A4]; int k; char pad4[8]; int h; };
int func_00130078(struct S *p, int c, int a, int b, int d, qword q);
void func_001309D8(int *ph);
void func_0027D608(struct S *p, int k)
{
    if (p->k != k) {
        p->k = k;
        if (k) {
            union { qword q; float f[4]; } v;
            v.q = Make(0.0f, -p->f1A0, p->f19C);
            p->h = func_00130078(p, p->x4C, 1, 5, 3, v.q);
        } else {
            func_001309D8(&p->h);
        }
    }
}
