// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int ParticleWord __attribute__((mode(TI)));

struct MotionApplyFrame {
    unsigned char beforeRelative[0xA0];
    void *relative;
    unsigned char beforePosition[0xF0 - 0xA4];
    ParticleWord position;
};

struct MotionApplyView {
    unsigned char beforeFrames[0x48];
    MotionApplyFrame *linearFrame;
    MotionApplyFrame *angularFrame;
};

extern "C" ParticleWord func_002445E8(void *, ParticleWord);
extern "C" ParticleWord func_00244630(void *, ParticleWord, ParticleWord);
extern "C" ParticleWord func_0028E990(void *, void *, ParticleWord);

static __inline__ ParticleWord AddParticleVectors(ParticleWord left,ParticleWord right)
{
    ParticleWord result;
    __asm__("vadd.xyzw %0,%1,%2" : "=j"(result) : "j"(left),"j"(right));
    return result;
}

static inline void AddMotionCorrection(MotionApplyFrame *frame, ParticleWord correction)
{
    ParticleWord previous = frame->position;
    ParticleWord relative = func_0028E990(0, frame->relative, correction);
    frame->position = AddParticleVectors(previous, relative);
}

extern "C" void func_00244770(void *receiver, ParticleWord point, ParticleWord impulse)
{
    MotionApplyView *motion = (MotionApplyView *)receiver;
    ParticleWord linear = func_002445E8(receiver, impulse);
    ParticleWord angular = func_00244630(receiver, point, impulse);
    AddMotionCorrection(motion->linearFrame, linear);
    AddMotionCorrection(motion->angularFrame, angular);
}
