// SLY3_CFLAGS: -Os -G0
extern int D_0036DBEC;
extern void *D_0036C328;
void *func_00167DA8(char *base,void *entry);
void *func_00292034(void *destination,int value,unsigned int bytes);
void func_00167D50(char *self)
{
    if((D_0036DBEC>>1)&1) func_00292034(func_00167DA8(self,D_0036C328),0,0x50);
    *(int *)(self+0x448)=0;
}
