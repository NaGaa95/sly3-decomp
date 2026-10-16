// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t,dt; };
extern struct CLOCK D_0036BB98;
struct EngineStampOwner { unsigned char prefix[0x250]; int mode; float since; };
void func_0015D908(void *owner);
void func_0015D8C8(struct EngineStampOwner *owner,int mode)
{
    if(mode!=owner->mode) {
        owner->mode=mode;
        owner->since=D_0036BB98.t;
        if(mode==2) func_0015D908(owner);
    }
}
