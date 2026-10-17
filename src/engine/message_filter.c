// SLY3_CFLAGS: -Os -G0
struct Message { void *target; int value; };
void func_00252440(void *self,int id,struct Message *message);
int func_002533C0(void *self,int index);
void func_001703C8(void *owner,int value,int flag);
struct Handler { unsigned char prefix[0x10D0]; void *owner; };
void func_0015F5D8(struct Handler *self,int id,struct Message *message)
{
    func_00252440(self,id,message);
    if(!func_002533C0(self,0x36) && id==0xC && message->target==self)
        func_001703C8(self->owner,message->value,1);
}
