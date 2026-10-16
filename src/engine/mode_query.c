// SLY3_CFLAGS: -Os -G0
struct EngineModeController { unsigned char prefix[0x50]; int busy; unsigned char gap[0x14]; int value; };
struct EngineModeSubject { unsigned char prefix[0xB0]; int value; };
extern struct EngineModeController *D_004BC244;
int func_00186900(struct EngineModeSubject *subject)
{
    struct EngineModeController *controller=D_004BC244;
    int busy=controller?controller->busy:-1;
    if(busy==0) return controller->value;
    return subject->value;
}
