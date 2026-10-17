// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct Mover { unsigned char prefix[0x9A]; short state; unsigned char gap9C[0x24]; U position; U velocity; };
extern int D_0036BB9C;
void func_0028B188(void *owner, struct Mover *mover);
void func_0028BFE8(void *owner, struct Mover *mover, qword target)
{
    if(mover->state==3) {
        U scale;
        qword delta;
        __asm__("vsub.xyzw %0,%1,%2" : "=j"(delta) : "j"(target), "j"(mover->position.q));
        __asm__("qmtc2.ni %1,%0" : "=j"(scale.q) : "r"(D_0036BB9C));
        __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(delta) : "j"(scale.q), "j"(delta));
        mover->velocity.q=delta;
    } else {
        float *velocity=mover->velocity.f;
        velocity[2]=0.0f;
        velocity[1]=0.0f;
        velocity[0]=0.0f;
    }
    mover->position.q=target;
    mover->state=3;
    func_0028B188(owner,mover);
}
