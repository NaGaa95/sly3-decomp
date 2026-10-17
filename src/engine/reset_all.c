// SLY3_CFLAGS: -Os -G0
struct ResetOwner { unsigned char prefix[0x10]; char *owner; };
void func_00238980(void);
void func_00160960(void *self,int mode,int flag);
void func_001614E8(void *self,int mode);
void func_0015FD58(void *self,int mode);
void func_00259D50(void *list);
void func_00252FC0(void *owner,int bit);
void func_00161C60(void *owner,int mode);
void func_0015F898(struct ResetOwner *self)
{
    func_00238980();
    func_00160960(self,-1,0);
    func_001614E8(self,-1);
    func_0015FD58(self,-1);
    func_00259D50(self->owner+0x4B0);
    func_00252FC0(self->owner,0x42);
    func_00161C60(self->owner,-1);
}
