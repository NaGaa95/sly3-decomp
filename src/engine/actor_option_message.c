// SLY3_CFLAGS: -Os -G0
struct ActorOptionOwner { unsigned char prefix[0x29C]; unsigned char collection[0]; };
struct ActorOptionMessage { int kind; unsigned int value; unsigned char unused[8]; };
void *func_00292034(void *destination,int value,unsigned int bytes);
void *func_002387A8(void *list,int key);
void func_0019A2D0(void *receiver,struct ActorOptionMessage *message);
void func_0015F6A0(struct ActorOptionOwner *owner,unsigned int value)
{
    struct ActorOptionMessage message;
    void *receiver;
    func_00292034(&message,0,sizeof(message));
    receiver=func_002387A8(owner->collection,0xC8);
    if(value) {
        message.value=value;
        message.kind=13;
        func_0019A2D0(receiver,&message);
    } else if(func_002387A8(owner->collection,0xDD)) {
        message.kind=1;
        func_0019A2D0(receiver,&message);
    }
}
