// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Channel { unsigned char prefix[0x70]; float rate; };
struct Channel *func_0028A600(void *owner,int mode);
void func_0028A640(void *owner,float duration)
{
    struct Channel *channel=func_0028A600(owner,1);
    if(duration==0.0f)
        channel->rate=0.0f;
    else
        channel->rate=1.0f/duration;
}
