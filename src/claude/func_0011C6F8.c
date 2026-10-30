// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* 3x3 matrix inverse (adjugate / determinant), returned by value. Operand-based VU asm; temporaries are clobbers. */
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
M3 func_0011C6F8(M3 *pm)
{
    M3 m;
    qword a, b, c;
    __asm__(
        "vopmula.xyz $ACC, %4, %5\n\t"
        "vopmsub.xyz %0, %5, %4\n\t"
        "vopmula.xyz $ACC, %5, %3\n\t"
        "vopmsub.xyz %1, %3, %5\n\t"
        "vopmula.xyz $ACC, %3, %4\n\t"
        "vopmsub.xyz %2, %4, %3\n\t"
        "vmul.xyz $vf6, %3, %0\n\t"
        "vmulax.w $ACC, $vf0, $vf6x\n\t"
        "vmadday.w $ACC, $vf0, $vf6y\n\t"
        "vmaddz.w $vf6, $vf0, $vf6z\n\t"
        "vadd.xyz $vf5, $vf0, %0\n\t"
        "vadd.xyz $vf4, $vf0, %1\n\t"
        "vdiv $Q, $vf0w, $vf6w\n\t"
        "vaddx.y %0, $vf0, %1x\n\t"
        "vaddx.z %0, $vf0, %2x\n\t"
        "vaddy.x %1, $vf0, $vf5y\n\t"
        "vaddy.z %1, $vf0, %2y\n\t"
        "vaddz.x %2, $vf0, $vf5z\n\t"
        "vaddz.y %2, $vf0, $vf4z\n\t"
        "vwaitq\n\t"
        "vmulq.xyz %0, %0, $Q\n\t"
        "vmulq.xyz %1, %1, $Q\n\t"
        "vmulq.xyz %2, %2, $Q"
        : "=&j"(a), "=&j"(b), "=&j"(c) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]) : "vf4", "vf5", "vf6");
    m.r[0] = a;
    m.r[1] = b;
    m.r[2] = c;
    return m;
}
