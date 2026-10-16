// SLY3_CFLAGS: -Os -G0
typedef int BaseUpdatePacked __attribute__((mode(TI)));
typedef struct BaseUpdateOwner {
    char prefix[0x1A0];
    BaseUpdatePacked vector;
} BaseUpdateOwner;
typedef struct BaseUpdateState {
    char prefix[0x10];
    BaseUpdateOwner *owner;
    char unaccessed14[0x30-0x14];
    int mode;
    int word34;
    void *extra;
    int word3C;
    void *source;
} BaseUpdateState;
extern BaseUpdatePacked D_00317560;
void func_002389A0(void *unused_receiver);
int func_00254EB8(void *source);
void func_00131610(void *state, int mode);
void func_00255038(void *source, void *owner);
void func_0024E920(void *owner, void *extra);

void func_001317B0(BaseUpdateState *state)
{
    int previous;
    func_002389A0(state);
    do {
        previous=state->mode;
        if(previous==0 && func_00254EB8(state->source))
            func_00131610(state,1);
    } while(previous!=state->mode);
    if(previous==0)
        func_00255038(state->source,state->owner);
    else
        state->owner->vector=D_00317560;
    if(state->extra)
        func_0024E920(state->owner,state->extra);
}
