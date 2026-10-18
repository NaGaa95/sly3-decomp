// SLY3_CFLAGS: -Os -G0
struct AnimationSlot {
    char prefix[8]; short saved, unused;
    float time; int active; void *sound;
};
struct AnimationSlots {
    char prefix[8]; struct AnimationSlot *slots;
    char gapC[4]; unsigned long ticks;
    float time; int saved, selected;
};
extern struct { unsigned long ticks; } D_0036BBE0;
void func_00244CA8(void *,float);
void func_002BBCD8(void **,void *);
void func_002672B8(void *,int);
static inline void Release(void **reference)
{
    if(reference && *reference) {
        func_00244CA8(*reference,0.0f);
        func_002BBCD8(reference,0);
    }
}
void func_00267888(struct AnimationSlots *owner,int index)
{
    struct AnimationSlot *slot=(struct AnimationSlot *)(index*sizeof(struct AnimationSlot)+(int)owner->slots);
    if(slot->saved>=0) {
        float time=slot->time;
        owner->saved=slot->saved;
        owner->time=time;
        owner->ticks=D_0036BBE0.ticks;
        owner->selected=-1;
        slot->saved=-1;
        slot->active=0;
        Release(&slot->sound);
    }
    func_002672B8(owner,index);
}
