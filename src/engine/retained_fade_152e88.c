// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int PackedPosition __attribute__((mode(TI)));
struct FadeMatrix { PackedPosition rows[4]; };
struct FadeEntry {
    short delta, unused;
    union { int (*state)(void *); struct FadeMatrix *(*matrix)(void *); } call;
};
struct FadeOwner {
    char prefix[0xC]; struct FadeEntry *vtable;
    char gap10[0xE44-0x10]; int mode;
    char gapE48[0x119C-0xE48]; void *space;
    int retained; float first, second;
};
extern struct { float time, delta; } D_0036BB98;
int func_00153158(void *owner);
void func_00173778(void *space,PackedPosition position,int ownerWord,void **output);
static inline float FadeMin(float a,float b) { return b<a?b:a; }
static inline float FadeMax(float a,float b) { return b>a?b:a; }
static inline float FadeClamp(float value,float low,float high)
{
    float result;
    if(value<low) result=low;
    else if(high<value) result=high;
    else result=value;
    return result;
}
void func_00152E88(struct FadeOwner *owner)
{
    int state;
    float value;
    if(!owner->space) return;
    switch(func_00153158(owner)) {
    case 1: {
        float delta=D_0036BB98.delta;
        owner->first=FadeMin(owner->first+2.0f*delta,1.0f);
    } break;
    case 0: {
        float delta=D_0036BB98.delta;
        owner->first=FadeMax(owner->first+-4.0f*delta,0.0f);
    } break;
    case 2: owner->first=0.0f; break;
    }
    if(owner->mode!=-1 || (value=owner->first)==0.0f) owner->retained=-1;
    else if(value==1.0f || (owner->retained==1 && 0.0f<value)) owner->retained=1;
    else owner->retained=0;
    state=owner->vtable[112].call.state((char *)owner+owner->vtable[112].delta);
    if(owner->retained!=1 && state==1) state=2;
    switch(state) {
    case 0: owner->second=0.0f; break;
    case 1: {
        float delta=D_0036BB98.delta;
        owner->second=FadeClamp(owner->second+4.0f*delta,0.0f,1.0f);
    } break;
    case -1: case 2: {
        float delta=D_0036BB98.delta;
        owner->second=FadeClamp(owner->second+-4.0f*delta,0.0f,1.0f);
    } break;
    }
    if(owner->second==1.0f) {
        struct FadeEntry *entry=&owner->vtable[36];
        struct FadeMatrix *matrix=entry->call.matrix((char *)owner+entry->delta);
        func_00173778(owner->space,matrix->rows[3],(int)owner,0);
    }
}
