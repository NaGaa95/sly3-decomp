// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct AnimationUpdateReferencePrefix { unsigned char unused[12]; };
class AnimationUpdateInterface : public AnimationUpdateReferencePrefix {
public:
    virtual void Retain();
    virtual void Release();
    virtual void UnusedMethod3();
    virtual void Notify(int event, int sender_word);
};
struct AnimationUpdateParent {
    unsigned char prefix[0x3C];
    unsigned int flags;
    unsigned char unused40[0x50];
    int event_count;
};
struct AnimationUpdateMethod { short delta, unused; void (*method)(); };
struct AnimationUpdateCurve { AnimationUpdateMethod *methods; };
struct AnimationUpdateLink {
    AnimationUpdateCurve *curve;
    float *output;
    unsigned char unused8[8];
    AnimationUpdateLink *next;
};
class AnimationUpdateRuntime : public AnimationUpdateInterface {
public:
    unsigned int word10;
    AnimationUpdateParent *parent;
    void *owner;
    float time, previous_time;
    unsigned char unused24[0x14];
    AnimationUpdateLink *evaluations;
    unsigned int flags;
    float rate;
    unsigned char unused44[0xC];
    int cursor;
};
class AnimationUpdateHold {
    AnimationUpdateRuntime *pointer;
public:
    AnimationUpdateHold(AnimationUpdateRuntime *p) : pointer(p) { p->Retain(); }
    ~AnimationUpdateHold() { pointer->Release(); }
};
struct AnimationUpdateClock {
    unsigned char prefix[4];
    float step;
    unsigned char unused8[0x3C];
    float alternate_step;
};
typedef char AnimationUpdateClockSize72[(sizeof(AnimationUpdateClock)==0x48)?1:-1];
extern AnimationUpdateClock D_0036BB98;
extern "C" void func_00137F60(void *);
extern "C" int func_00138AC8(void *);
extern "C" int func_00138938(void *,float *,float *);
extern "C" void func_00137B00(void *);
static __inline__ unsigned int AnimationUpdateFlags(AnimationUpdateParent *parent)
{
    unsigned int flags = parent->flags;
    return ((flags ^ 1) & 1) ? *(unsigned int *)flags : flags;
}
extern "C" void func_00137900(void *receiver)
{
    AnimationUpdateRuntime *runtime = (AnimationUpdateRuntime *)receiver;
    if (__builtin_fabsf(runtime->rate) < 0.0001f)
        return;
    AnimationUpdateHold retained(runtime);
    if (AnimationUpdateFlags(runtime->parent) & 0x200)
        runtime->time = runtime->time + runtime->rate * D_0036BB98.alternate_step;
    else
        runtime->time = runtime->time + runtime->rate * D_0036BB98.step;
    func_00137F60(runtime);
    if (func_00138AC8(runtime))
        return;
    int wrapped = func_00138938(runtime,&runtime->time,&runtime->rate);
    if (wrapped) {
        if (runtime->flags & 8)
            runtime->cursor = runtime->rate <= 0.0f ? runtime->parent->event_count : 0;
    }
    if (wrapped) {
        runtime->Notify(5,(int)runtime);
        if (func_00138AC8(runtime))
            return;
    }
    if (wrapped && !(runtime->flags & 0x38))
        func_00137B00(runtime);
    else {
        func_00137F60(runtime);
        if (func_00138AC8(runtime))
            return;
    }
    for (AnimationUpdateLink *link = runtime->evaluations; link; link = link->next) {
        AnimationUpdateCurve *curve = link->curve;
        ((void (*)(void *,float *,float *,float,float))curve->methods[2].method)
            ((char *)curve + curve->methods[2].delta,link->output,0,runtime->time,runtime->rate);
    }
}
