// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
extern qword D_00317540;
extern qword D_00317550;
void func_0011C8C0(M3 *pm, float g, qword axis);
void *func_00291E8C(void *pvDst, void *pvSrc, int cb);
static inline M3 MulM3(M3 *pa, M3 *pb)
{
    M3 m;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(m.r[0]) : "j"(pa->r[0]), "j"(pa->r[1]), "j"(pa->r[2]), "j"(pb->r[0]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(m.r[1]) : "j"(pa->r[0]), "j"(pa->r[1]), "j"(pa->r[2]), "j"(pb->r[1]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(m.r[2]) : "j"(pa->r[0]), "j"(pa->r[1]), "j"(pa->r[2]), "j"(pb->r[2]));
    return m;
}
M3 *func_0011CAE0(M3 *pm, float g1, float g2)
{
    M3 c;
    M3 a;
    M3 b;
    func_0011C8C0(&a, g1, D_00317550);
    func_0011C8C0(&b, -g2, D_00317540);
    c = MulM3(&a, &b);
    func_00291E8C(pm, &c, sizeof(M3));
    return pm;
}
