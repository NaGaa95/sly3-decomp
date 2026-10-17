// SLY3_CFLAGS: -Os -G0
void func_0023AE08(void *);
void func_00280430(char *receiver)
{
    unsigned int value;
    func_0023AE08(receiver);
    value=*(unsigned int *)(receiver+0x3C);
    *(int *)(receiver+0x15C)=1;
    *(int *)(receiver+0x160)=0x2000;
    *(int *)(receiver+0x164)=10;
    *(int *)(receiver+0x16C)=0x13;
    if((value^1)&1)*(unsigned int *)value|=2;
    else *(unsigned int *)(receiver+0x3C)=value|2;
}
