// SLY3_CFLAGS: -Os -G0
struct ResetSelf { unsigned char prefix[0x10]; void *owner; unsigned char gap14[0x74-0x14]; int word74; };
void func_00238980(void);
void func_0018BB20(void *self,int mode);
void func_0018BF48(void *self,int flag);
void func_00252FC0(void *owner,int bit);
void *func_001FC118(void *owner);
void func_001FC090(void *object,void *owner);
void func_0018B780(struct ResetSelf *self)
{
    func_00238980();
    func_0018BB20(self,-1);
    func_0018BF48(self,-1);
    func_00252FC0(self->owner,0x40);
    if(self->word74) {
        func_001FC090(func_001FC118(self->owner),self->owner);
        self->word74=0;
    }
}
