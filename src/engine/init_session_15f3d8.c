// SLY3_CFLAGS: -Os -G0
struct Shuffled;
extern void *D_0036B334;
extern char D_0036B118[];
void func_00250868(void *self);
void func_0024F188(void *self,float value);
void func_001F4460(void *self,int value);
void *func_001D27F0(unsigned int bytes);
struct Shuffled *func_002BC1C8(void *storage,int count,const int *identifiers,void *heap);
void func_0015F3D8(char *self)
{
    func_00250868(self);
    D_0036B334=self;
    *(int *)(self+0x164)=0x40;
    *(int *)(self+0x18B0)=-1;
    func_0024F188(self,1.6f);
    func_001F4460(self,100);
    {
        int identifiers[4]={50,51,52,53};
        *(float *)(self+0x187C)=6000.0f;
        *(struct Shuffled **)(self+0x18AC)=func_002BC1C8(func_001D27F0(20),4,identifiers,D_0036B118);
    }
}
