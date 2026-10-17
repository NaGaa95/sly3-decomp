// SLY3_CFLAGS: -Os -G0
struct HoldSelf { unsigned char prefix[0x10]; void *owner; unsigned char gap14[0x74-0x14]; int word74; };
void func_00238978(void *self);
void func_0018BB20(void *self,int mode);
void func_0018BF48(void *self,int flag);
void *func_001FC118(void *owner);
int func_001FC0B8(void *object,void *owner);
void func_001FC060(void *object,void *owner);
void func_0018B700(struct HoldSelf *self)
{
    void *object;
    func_00238978(self);
    func_0018BB20(self,0);
    func_0018BF48(self,0);
    object=func_001FC118(self->owner);
    if(object) {
        if(!func_001FC0B8(object,self->owner)) {
            func_001FC060(object,self->owner);
            self->word74=1;
        }
    }
}
