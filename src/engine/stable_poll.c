// SLY3_CFLAGS: -Os -G0
int func_00238AD0(void *object);
void func_0018BF48(void *object,int flag);
struct PollObject { unsigned char prefix[0x3C]; int state; };
void func_0018BEE8(struct PollObject *object)
{
    int seen;
    do {
        seen=object->state;
        if(!seen && func_00238AD0(object)) func_0018BF48(object,1);
    } while(seen!=object->state);
}
