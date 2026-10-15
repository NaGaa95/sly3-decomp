// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct AnimationCancelPrefix { unsigned char unused[12]; };
class AnimationCancelInterface : public AnimationCancelPrefix {
public:
    virtual void Retain();
    virtual void Release();
    virtual void Message(int event,void *argument,int count,void *parameters,void *result);
};
struct AnimationCancelMethod { short delta,unused; void (*method)(); };
struct AnimationCancelOwner {
    unsigned char prefix[12];
    AnimationCancelMethod *methods;
};
struct AnimationCancelEvent { float time; unsigned char unused[16]; };
struct AnimationCancelParent {
    unsigned char prefix[0x98];
    int count;
    AnimationCancelEvent *events;
};
struct AnimationCancelBinding {
    unsigned char prefix[4];
    void *owner;
    void *channel;
    unsigned char unusedC[0x1C];
    AnimationCancelBinding *next;
};
struct AnimationCancelEvaluation {
    void *record;
    float *output;
    AnimationCancelOwner *owner;
    int key;
    AnimationCancelEvaluation *next;
};
class AnimationCancelRuntime : public AnimationCancelInterface {
public:
    unsigned int word10;
    AnimationCancelParent *parent;
    AnimationCancelOwner *owner;
    float time,previous_time;
    unsigned char unused24[0x10];
    AnimationCancelBinding *bindings;
    AnimationCancelEvaluation *evaluations;
    unsigned char unused3C[0x18];
    int cursor;
    int enabled;
    void *reference;
};
class AnimationCancelHold {
    AnimationCancelRuntime *pointer;
public:
    AnimationCancelHold(AnimationCancelRuntime *p):pointer(p) { p->Retain(); }
    ~AnimationCancelHold() { pointer->Release(); }
};
extern unsigned char D_00479994[];
extern "C" {
int func_00138AC8(void *);
void func_00138270(void *,AnimationCancelEvent *);
void func_00138AF0(void *,int);
void func_0011B028(void *,void *);
void func_0028EDC8(void *,void *,void *);
void func_001306C8(void *);
void func_0012F260(void *);
void func_002BBCD8(void **,void *);
void func_0013BE38(void *,int,int);
}
extern "C" void func_00137B00(void *receiver)
{
    AnimationCancelRuntime *runtime=(AnimationCancelRuntime *)receiver;
    if(func_00138AC8(runtime)) return;
    AnimationCancelHold retained(runtime);
    for(;runtime->cursor<runtime->parent->count;++runtime->cursor) {
        AnimationCancelEvent *event=&runtime->parent->events[runtime->cursor];
        event->time=runtime->time;
        func_00138270(runtime,event);
        if(func_00138AC8(runtime)) return;
    }
    func_00138AF0(runtime,0);
    func_0011B028(D_00479994,runtime);
    func_0011B028((char *)runtime->parent+0x40,runtime);
    AnimationCancelBinding *binding,*next_binding;
    for(binding=runtime->bindings;binding;binding=next_binding) {
        next_binding=binding->next;
        func_0028EDC8(binding->owner,binding->channel,binding);
        func_001306C8(binding);
    }
    runtime->bindings=0;
    AnimationCancelEvaluation *evaluation,*next_evaluation;
    for(evaluation=runtime->evaluations;evaluation;evaluation=next_evaluation) {
        AnimationCancelOwner *owner=evaluation->owner;
        next_evaluation=evaluation->next;
        ((void (*)(void *,int))owner->methods[49].method)
            ((char *)owner+owner->methods[49].delta,evaluation->key);
        func_0012F260(evaluation);
    }
    runtime->evaluations=0;
    func_002BBCD8(&runtime->reference,0);
    runtime->Message(3,0,0,0,0);
    if(runtime->owner) {
        AnimationCancelOwner *owner=runtime->owner;
        ((void (*)(void *,int,int))owner->methods[5].method)
            ((char *)owner+owner->methods[5].delta,4,(int)runtime);
    }
    func_0013BE38(runtime,4,(int)runtime);
    runtime->Release();
}
