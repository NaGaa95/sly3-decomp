// SLY3_CFLAGS: -Os -G0
void func_001F4500(void *self,void *arg);
void *func_00169BF8(int size);
void func_0019F8B0(void *request,void *arg,int kind,void *self,int word);
struct SpawnOwner { unsigned char prefix[0x30C]; int word30C; };
void func_0019BF08(struct SpawnOwner *self,void *arg)
{
    if(!self->word30C) {
        func_001F4500(self,arg);
        return;
    }
    func_0019F8B0(func_00169BF8(0x50),arg,0xC,self,self->word30C);
}
