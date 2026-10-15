// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct ActorReferenceMethod {
    short delta,unused;
    union { void (*reference)(void *); void (*kind)(void *,int); void (*pointer)(void *,void *); } call;
};
struct ActorRetainedReference {
    char prefix[0xC]; ActorReferenceMethod *methods;
    char before_kind[0x48-0x10]; const unsigned char *command;
};
struct ActorReferenceOwner {
    char prefix[0xC]; ActorReferenceMethod *methods;
    char before_context[0x508-0x10]; int context_state;
    char before_reference[0x115C-0x50C]; ActorRetainedReference *reference;
    char before_kind[0x1294-0x1160]; int kind;
    char before_input[0x1440-0x1298]; void *input;
};
extern "C" {
void func_00238568(void *);
int func_00156998(void *);
void func_001BDBB0(void *,int);
}
static inline void ActorReferenceReset(ActorReferenceOwner *owner)
{
    ActorReferenceMethod *m=&owner->methods[99];
    m->call.kind((char *)owner+m->delta,0);
}
extern "C" void func_00156468(ActorReferenceOwner *owner,ActorRetainedReference *reference)
{
    ActorRetainedReference *old=owner->reference;
    if(reference==old) return;
    if(old) {
        ActorReferenceMethod *m=&old->methods[2];
        m->call.reference((char *)old+m->delta);
        switch(owner->context_state) {
        case 5: case 6: ActorReferenceReset(owner); break;
        }
    }
    owner->reference=reference;
    if(reference) {
        ActorReferenceMethod *m=&reference->methods[1];
        m->call.reference((char *)reference+m->delta);
        func_00238568((char *)owner+0x29C);
        if(func_00156998(owner)) func_001BDBB0((char *)owner+0xF60,-1);
        if(owner->kind!=-1 && *owner->reference->command!=0x2A) ActorReferenceReset(owner);
    }
    ActorReferenceMethod *m=&owner->methods[84];
    m->call.pointer((char *)owner+m->delta,owner->input);
}
