// SLY3_CFLAGS: -O2 -G0
extern void func_0029F960(unsigned int *channel);
int func_0029FDE8(unsigned int *channel,int mode,int timeout)
{
    int result;
    if(mode==1) result=(*channel>>8)&1;
    else { func_0029F960(channel); result=0; }
    return result;
}
