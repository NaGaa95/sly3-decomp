// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
extern int D_0036DBEC;
extern qword D_00326E70;
void func_00236A78(qword *color)
{
    if((D_0036DBEC>>1)&1) {
        union { qword q; float f[4]; } gray;
        register qword value __asm__("vf1")=*color;
        register qword weights __asm__("vf2")=D_00326E70;
        qword one;
        float level;
        __asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "+j"(value), "=j"(one) : "j"(weights));
        __asm__("mtc1 %1,%0" : "=f"(level) : "r"(value));
        gray.q=0;
        gray.f[0]=level;
        gray.f[1]=level;
        gray.f[2]=level;
        *color=gray.q;
    }
}
