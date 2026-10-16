// SLY3_CFLAGS: -Os -G0
struct EngineModeOwner { unsigned char prefix[0x394]; int mode; };
void func_00144628(struct EngineModeOwner *owner,int mode){if(mode!=owner->mode)owner->mode=mode;}
