// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t,dt; };
extern struct CLOCK D_0036BB98;
struct EngineHookSubject { unsigned char prefix[0x30]; int state; float since; unsigned char gap[4]; int flag; };
void func_00238A38(void *subject);
void func_002389C0(void *subject);
void func_00238AB8(void *subject);
void func_001591E8(struct EngineHookSubject *subject,int state)
{
    if(state==subject->state) return;
    if(subject->state==2) func_00238A38(subject);
    subject->state=state;
    subject->since=D_0036BB98.t;
    if(state!=-1) {
        if(state==2) {
            func_002389C0(subject);
            subject->flag=1;
        }
    } else func_00238AB8(subject);
}
