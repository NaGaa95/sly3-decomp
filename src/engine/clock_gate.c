// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t,dt; };
extern struct CLOCK D_0036BB98;
struct GateOwner { unsigned char prefix[0x3D8]; int word3D8; unsigned char gap3DC[0x1080-0x3DC]; float deadline; };
struct GateSelf { unsigned char prefix[0x10]; struct GateOwner *owner; unsigned char gap14[0x30-0x14]; int word30; };
int func_001A3BA8(struct GateOwner *owner,int a,int b);
int func_00135758(struct GateSelf *self)
{
    int result=func_001A3BA8(self->owner,self->word30,self->owner->word3D8);
    if(result) return result;
    if(self->owner->deadline<D_0036BB98.t) self->owner->deadline=D_0036BB98.t+0.25f;
    return 0;
}
