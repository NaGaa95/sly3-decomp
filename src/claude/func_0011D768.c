// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Inverse of a rigid 4x4 transform (3x3 adjugate / determinant, negated position rotated back), returned by value.
   Sly 2 counterpart: func_0011C318 (register-pinned there).  Matching notes: the rows are loaded into locals in
   order r0, r1, r2, pos (local-alloc then gives vf3/vf2/vf1/vf4), and pos is a plain "j" input that the block
   negates in place, so the earlyclobber outputs get reload registers vf7-vf10 copied back with vmove like the target. */
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
M4 func_0011D768(M4 *pm)
{
    M4 m;
    qword a, b, c, d, p, r0, r1, r2;
    r0 = pm->r[0];
    r1 = pm->r[1];
    r2 = pm->r[2];
    p = pm->r[3];
    __asm__(
        "vopmula.xyz $ACC, %6, %7\n\t"
        "vopmsub.xyz %0, %7, %6\n\t"
        "vopmula.xyz $ACC, %7, %5\n\t"
        "vopmsub.xyz %1, %5, %7\n\t"
        "vopmula.xyz $ACC, %5, %6\n\t"
        "vopmsub.xyz %2, %6, %5\n\t"
        "vmul.xyz $vf6, %5, %0\n\t"
        "vmulax.w $ACC, $vf0, $vf6x\n\t"
        "vmadday.w $ACC, $vf0, $vf6y\n\t"
        "vmaddz.w $vf6, $vf0, $vf6z\n\t"
        "vadd.xyz $vf6, $vf0, %0\n\t"
        "vadd.xyz $vf5, $vf0, %1\n\t"
        "vsub.xyz %4, $vf0, %4\n\t"
        "vdiv $Q, $vf0w, $vf6w\n\t"
        "vaddx.y %0, $vf0, %1x\n\t"
        "vaddx.z %0, $vf0, %2x\n\t"
        "vaddy.x %1, $vf0, $vf6y\n\t"
        "vaddy.z %1, $vf0, %2y\n\t"
        "vaddz.x %2, $vf0, $vf6z\n\t"
        "vaddz.y %2, $vf0, $vf5z\n\t"
        "vmulq.xyz %0, %0, $Q\n\t"
        "vsub.w %0, $vf0, $vf0\n\t"
        "vmulq.xyz %1, %1, $Q\n\t"
        "vsub.w %1, $vf0, $vf0\n\t"
        "vmulq.xyz %2, %2, $Q\n\t"
        "vsub.w %2, $vf0, $vf0\n\t"
        "vmulax.xyz $ACC, %0, %4x\n\t"
        "vmadday.xyz $ACC, %1, %4y\n\t"
        "vmaddz.xyz %3, %2, %4z\n\t"
        "vaddx.w %3, $vf0, $vf0x"
        : "=&j"(a), "=&j"(b), "=&j"(c), "=&j"(d) : "j"(p), "j"(r0), "j"(r1), "j"(r2) : "vf5", "vf6");
    m.r[0] = a;
    m.r[1] = b;
    m.r[2] = c;
    m.r[3] = d;
    return m;
}
