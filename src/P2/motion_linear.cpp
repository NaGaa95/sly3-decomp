// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int ParticleWord __attribute__((mode(TI)));
struct MotionDeltaFrame {
    unsigned char beforeKind[0x98];
    short kind;
    unsigned char beforeRelative[0xA0-0x9A];
    void *relative;
    unsigned char beforePosition[0xF0-0xA4];
    ParticleWord position;
};
struct MotionDeltaView {
    unsigned char beforeFrames[0x48];
    MotionDeltaFrame *linearFrame;
    MotionDeltaFrame *angularFrame;
};
extern "C" int func_0028F048(int kind);
extern "C" ParticleWord func_0028E990(void *,void *,ParticleWord);
static __inline__ ParticleWord AddParticleVectors(ParticleWord left,ParticleWord right)
{
    ParticleWord result;
    __asm__("vadd.xyzw %0,%1,%2" : "=j"(result) : "j"(left),"j"(right));
    return result;
}
extern "C" void func_00244828(void *receiver,ParticleWord correction)
{
    MotionDeltaView *motion=(MotionDeltaView *)receiver;
    if (func_0028F048(motion->linearFrame->kind)) {
        MotionDeltaFrame *frame=motion->linearFrame;
        ParticleWord previous=frame->position;
        ParticleWord relative=func_0028E990(0,frame->relative,correction);
        frame->position=AddParticleVectors(previous,relative);
    }
}
