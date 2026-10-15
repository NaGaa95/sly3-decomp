// Sly 2 func_0015B0C8, retaining its ordinary C union lifetime.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct P { char pad[12]; float scale; char pad1[0x38-0x10]; float spread,lifetime; char pad2[8]; float lo,hi,age_lo,age_hi; };
struct CLOCK { float time; };
extern struct CLOCK D_0036BB98;
void func_00178CD8(void *,float,float,struct P *,qword *,int,qword *);
float func_0011E940(float,float);
void func_00178E98(struct P *p,void *sampling,void *unused,int index,qword *position,qword *direction,qword *velocity,float *birth,float *death)
{
    float time,displacement;
    func_00178CD8(sampling,p->spread,p->scale,p,direction,index,velocity);
    time=D_0036BB98.time;
    time=time-func_0011E940(p->age_lo,p->age_hi);
    *birth=time;
    *death=time+p->lifetime;
    displacement=func_0011E940(p->lo,p->hi);
    if(displacement!=0.0f) {
        U scalar;
        qword result;
        __asm__("qmtc2.ni %1,%0" : "=j"(scalar.q) : "r"(displacement));
        __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x"
            : "=j"(result) : "j"(*position),"j"(*velocity),"j"(scalar.q));
        *position=result;
    }
}
