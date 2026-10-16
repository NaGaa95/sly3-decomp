// SLY3_CFLAGS: -Os -G0
struct EnginePairObject { unsigned char prefix[0x448]; int flag; };
struct EnginePairObject *func_001750B0(int input);
void func_00168AB0(void *object,int a,int b,void *p);
void func_001751C0(int input,void *unused,void *p)
{
    struct EnginePairObject *object=func_001750B0(input);
    func_00168AB0(object,1,object->flag==0?3:2,p);
}
