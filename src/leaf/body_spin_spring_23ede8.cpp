// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Turn the owner body toward a target orientation: the rotation still needed (angle about an axis) is smoothed with
// GSmooth, the resulting spin rate gives a target angular velocity, and the torque that reaches it within one frame is
// clamped to 1.25 * (gA - gB) / gC. When the smoothing lands on the target this frame, the angular velocity is set
// directly instead. Same body view as the neighbouring steer-force function (body_steer_force_23efa0.cpp).
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {U rows[3];M3(){} M3(const M3&m){rows[0]=m.rows[0];rows[1]=m.rows[1];rows[2]=m.rows[2];} M3&operator=(const M3&m){rows[0]=m.rows[0];rows[1]=m.rows[1];rows[2]=m.rows[2];return *this;}};
struct OWNER {M3 matrix;char pad30[0x70];OWNER *parent;char padA4[0xC];qword angularVelocity;char padC0[0x30];qword torque;};
struct P {char pad4C[0x4C];OWNER *owner;};
struct SMP {float gA,gB,gC;};
struct CLOCK {float t,dt;};
extern CLOCK D_0036BB98;
extern "C" M3 func_0028EA00(OWNER *,OWNER *,const M3 *);
extern "C" void func_0011C798(M3 *);
extern "C" M3 func_0011CFC0(const M3 *,const M3 *);
extern "C" void func_0011D0B8(const M3 *,float *,qword *);      /* DecomposeRotateMatrixRad */
extern "C" float func_0011E598(const SMP *,float *,float,float,float); /* GSmooth */
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword ScaleX(qword v,qword s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(s));return r;}
static inline qword DivBy(qword v,qword s){qword r;__asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(r):"j"(v),"j"(s));return r;}
static inline float Length(qword a){qword d,one;float f;
__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(a));
__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(d):"0"(d));
__asm__("mtc1 %1,%0":"=f"(f):"r"(d));return f;}
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword ScalarI(int f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"rV"(f));return q;}
static inline qword Splat(U &holder,float f){qword k=Scalar(f);holder.q=k;return k;}
static inline qword SplatI(U &holder,int f){qword k=ScalarI(f);holder.q=k;return k;}
extern "C" void func_0023EDE8(P*p,const M3*orientation,const SMP*smp)
{
    OWNER *owner=p->owner;
    M3 target=func_0028EA00(0,owner->parent,orientation);
    func_0011C798(&target);
    M3 relative=func_0011CFC0(&owner->matrix,&target);
    U axis,scalar;
    float angle,rate;
    func_0011D0B8(&relative,&angle,&axis.q);
    float smoothed=func_0011E598(smp,&rate,0.0f,angle,D_0036BB98.dt);
    float limit=(smp->gA-smp->gB)/smp->gC*1.25f;
    qword k1=ScalarI(*(int *)&rate);
    scalar.q=k1;
    qword velocity=ScaleX(axis.q,k1);
    qword error=Sub(velocity,owner->angularVelocity);
    qword k2=Scalar(D_0036BB98.dt);
    scalar.q=k2;
    qword torque=DivBy(error,k2);
    float length=Length(torque);
    if(limit<length){
        torque=ScaleX(torque,Splat(scalar,limit/length));
    } else if(smoothed==angle){
        qword w=ScaleX(axis.q,Splat(scalar,(angle+angle)/D_0036BB98.dt));
        owner->angularVelocity=w;
        qword neg=ScaleX(w,Splat(scalar,-1.0f));
        torque=DivBy(neg,SplatI(scalar,*(int *)&D_0036BB98.dt));
    }
    owner->torque=Add(owner->torque,torque);
}
