// SLY3_CFLAGS: -Os -G0
struct EngineDispatchController { unsigned char prefix[0x50]; int busy; };
struct EngineDispatchSubject { unsigned char prefix[0xC8]; int handle; };
extern struct EngineDispatchController *D_004BC244;
void func_001878E0(void *subject,int mode);
void func_00186FE8(void *subject);
void func_00186F90(struct EngineDispatchSubject *subject)
{
    struct EngineDispatchController *controller=D_004BC244;
    int busy=controller?controller->busy:-1;
    if(busy==0 || subject->handle!=-1) func_001878E0(subject,5);
    else func_00186FE8(subject);
}
