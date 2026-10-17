// SLY3_CFLAGS: -Os -G0
extern int D_0046F568;
extern unsigned char D_00475480[];
int func_0025E150(void);
void *func_001F4AD0(void *game,int index);
int func_0013B500(void *object,int id);
void func_0013BC80(void *object);
void func_001641B0(void)
{
    void *object;
    if(func_0025E150()!=0x15) return;
    if(D_0046F568==-1) return;
    object=func_001F4AD0(D_00475480,D_0046F568);
    if(!object) return;
    if(func_0013B500(object,0x52)) func_0013BC80(object);
}
