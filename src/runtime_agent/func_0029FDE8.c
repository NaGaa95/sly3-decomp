// SLY3_CFLAGS: -O2 -G0
// Sly2 SDK sceDmaSync interface, including its unused timeout formal.
// Ordinary C common-result join; actual original channel/mode are forwarded.
extern int func_0029F960(unsigned int *channel,int mode);
int func_0029FDE8(unsigned int *channel,int mode,int timeout)
{
    int result;
    if(mode==1) result=(*channel>>8)&1;
    else { func_0029F960(channel,mode); result=0; }
    return result;
}
