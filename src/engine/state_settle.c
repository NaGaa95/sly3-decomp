// SLY3_CFLAGS: -Os -G0
struct EngineSettleSubject { unsigned char prefix[0x30]; int state; };
void func_002389A0(void *subject);
int func_00238AD0(void *subject);
void func_0016E6C0(void *subject,int value);
void func_0016E650(struct EngineSettleSubject *subject)
{
    int state;
    func_002389A0(subject);
    do {
        state=subject->state;
        if(state<4) {
            if(state>=0) {
                if(func_00238AD0(subject)) func_0016E6C0(subject,-1);
            }
        }
    } while(state!=subject->state);
}
