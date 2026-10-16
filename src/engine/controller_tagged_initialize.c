// SLY3_CFLAGS: -Os -G0
void func_0023AE08(void *);
void func_0015BDF8(char *);
void func_0015C6D0(char *receiver) {
    unsigned int value;
    func_0023AE08(receiver);
    func_0015BDF8(receiver+0x130);
    *(int *)(receiver+0x224)=-1;
    value=*(unsigned int *)(receiver+0x3C);
    if((value^1)&1)*(unsigned int *)value|=2;
    else *(unsigned int *)(receiver+0x3C)=value|2;
}
