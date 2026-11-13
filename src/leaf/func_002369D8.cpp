// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
extern int D_0036DBEC;
extern qword D_00326E70;
extern float D_0036BC9C;
union Vec { qword q; float f[4]; };
static inline qword Splat(Vec &home, float g)
{
    qword s;
    __asm__("qmtc2.ni %1,%0" : "=j"(s) : "r"(g));
    // Keep the scalar vector in its temporary stack home.
    *(volatile qword *)&home.q = s;
    return s;
}
extern "C" void func_002369D8(qword *color)
{
    if ((D_0036DBEC >> 1) & 1) {
        Vec gray;
        qword one;
        register float level __asm__("$f1"); /* original gray level register */
        qword value;
        qword weights;
        float amount;
        float keep;
        // Preserve the original order of the stack initialization and color load.
        *(volatile qword *)&gray.q = 0;
        value = *(volatile qword *)color;
        weights = D_00326E70;
        amount = D_0036BC9C;
        keep = 1.0f - amount;

        __asm__("vmul.xyz %0,%2,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "+j"(weights), "=&j"(one) : "j"(value));
        __asm__("mtc1 %1,%0" : "=f"(level) : "r"(weights));
        gray.f[0] = level;
        gray.f[1] = level;
        gray.f[2] = level;
        Vec scalar;
        qword scale = Splat(scalar, keep);
        qword amountq = Splat(scalar, amount);
        qword result = scale;
        __asm__("vmulax.xyzw $ACC,%1,%0x\n\tvmaddx.xyzw %0,%2,%3x" : "+j"(result) : "j"(value), "j"(gray.q), "j"(amountq));
        *color = result;
    }
}
