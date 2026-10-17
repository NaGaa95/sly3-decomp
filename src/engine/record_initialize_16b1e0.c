// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
extern Qword D_00317560;
void func_00169E28(void *self);
void func_001679E0(void *owner,float value);
void func_00167960(void *owner,float value);
void *func_00130078(void *owner,void *channel,int a,int b,int c,Qword value);
struct InitSelf { void *owner; unsigned char gap4[0x20-4]; void *first; void *second; void *task; float stamp; };
void func_0016B1E0(struct InitSelf *self)
{
    func_00169E28(self);
    func_001679E0(self->owner,25.0f);
    func_00167960(self->owner,1.15f);
    self->task=func_00130078(self->first,self->second,1,9,3,D_00317560);
    self->stamp=-1.0f;
}
