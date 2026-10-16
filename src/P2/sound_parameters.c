// SLY3_CFLAGS: -Os -G0
struct SoundParameterState {
    unsigned char prefix[0x14]; int parameter; float rate;
    unsigned char gap1C[0x44-0x1C]; int handle; float gain;
    unsigned char gap4C[4]; int rateBias;
    unsigned char gap54[8]; unsigned short flags;
};
void func_002911B0(int,int,int,int,int,int);
void func_00245DE0(struct SoundParameterState *state)
{
    int flags=state->flags;
    if(flags&0x70) {
        int mask=0;
        int gainWord,rateWord;
        if(flags&0x10) {mask=1;gainWord=(int)(state->gain*1024.0f);}
        if(flags&0x20) mask|=4;
        if(flags&0x40) {mask|=8;rateWord=(int)(state->rate*1524.0f)+state->rateBias;}
        func_002911B0(state->handle,mask,gainWord,state->parameter,rateWord,0);
    }
}
