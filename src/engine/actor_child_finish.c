// SLY3_CFLAGS: -Os -G0
struct ActorChildFinishMethod { short adjustment,unused; void (*method)(void *,int); };
struct ActorChildFinishChild { char prefix[12]; struct ActorChildFinishMethod *methods; };
struct ActorChildFinishOwner { char prefix[0x19A4]; struct ActorChildFinishChild *child; };
void func_0013F8D0(void *receiver);
void func_001B7268(void *context,int kind,void *resource,void *record,float gain);
void func_0013F870(struct ActorChildFinishOwner *receiver,int mode)
{
    struct ActorChildFinishChild *child=receiver->child;
    child->methods[80].method((char *)child+child->methods[80].adjustment,mode);
    func_0013F8D0(receiver);
    func_001B7268((char *)receiver+0x320,11,0,0,1.0f);
}
