// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Pattern { int count; unsigned char gap4[4]; float rate; };
struct Channel { unsigned char prefix[8]; int state; struct Pattern *pattern; int position; float gain; float rate; };
int func_00210DE0(struct Channel *channel);
void func_00210C90(struct Channel *channel,int mode);
void func_00210C08(struct Channel *channel,struct Pattern *pattern,float gain)
{
    if(func_00210DE0(channel)) {
        if(channel->state==5||channel->state==0)
            return;
        if(pattern->count<=0)
            return;
        channel->gain=gain;
        channel->pattern=pattern;
        channel->position=0;
        channel->rate=pattern->rate;
        channel->state=-1;
        func_00210C90(channel,2);
    }
}
