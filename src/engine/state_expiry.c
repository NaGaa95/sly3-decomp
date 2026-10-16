// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t,dt; };
extern struct CLOCK D_0036BB98;
struct EngineExpiryOwner { unsigned char prefix[0x2C0]; int state; unsigned char gap[4]; float start; unsigned char gap2[8]; float limit; };
void func_001434A8(struct EngineExpiryOwner *owner,int state);
void func_00143AB8(struct EngineExpiryOwner *owner)
{
    int state;
    do {
        state=owner->state;
        if(state<3) {
            if(state>=0) {
                if(owner->limit<D_0036BB98.t-owner->start) func_001434A8(owner,3);
            }
        }
    } while(state!=owner->state);
}
