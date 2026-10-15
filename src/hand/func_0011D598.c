// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
qword ml(const M4 *m, qword v) __asm__("func_0011D598");
qword ml(const M4 *m, qword v)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmadday.xyzw $ACC, %3, %1y\n\tvmaddaz.xyzw $ACC, %4, %1z\n\tvmaddw.xyzw %0, %5, %1w"
            : "=j"(r) : "j"(v), "j"(m->r[0]), "j"(m->r[1]), "j"(m->r[2]), "j"(m->r[3]));
    return r;
}
