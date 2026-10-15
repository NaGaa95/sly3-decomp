// SLY3_CFLAGS: -Os -G0
struct ActorMessageOwner { char prefix[0x1520]; int state; };
int func_001B5DD8(void *context);
int func_00153668(void *receiver,int message);
int func_0013F3B0(struct ActorMessageOwner *receiver,int message)
{
    if(receiver->state==3 && func_001B5DD8((char *)receiver+0x500))
        return 1;
    return func_00153668(receiver,message);
}
int func_0013F408(struct ActorMessageOwner *receiver)
{
    switch(receiver->state) {
    case 0: case 1: case 5: case 6: case 7: case 9: return 1;
    }
    return 0;
}
