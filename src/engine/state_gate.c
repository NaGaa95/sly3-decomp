// SLY3_CFLAGS: -Os -G0
int func_0019B6E0(void *self);
int func_001F43C8(void *self);
void func_0019DC10(void *self,int mode);
struct GateMessage { unsigned char prefix[0x14]; int value; };
struct GateObject { unsigned char prefix[0x1F0]; int state; unsigned char gap[0x3F8-0x1F4]; int word3F8; };
int func_0019DBA8(struct GateObject *object,struct GateMessage *message)
{
    if(object->state==4 || object->state==5) return 0;
    object->word3F8=message->value;
    if(!func_0019B6E0(object)) return 0;
    if(func_001F43C8(object)>0) func_0019DC10(object,4);
    return 1;
}
