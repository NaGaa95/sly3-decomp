// SLY3_CFLAGS: -Os -G0
typedef struct WaitBindDescriptor {
    char unaccessed[0x1C];
    struct WaitBindDescriptor *next;
} WaitBindDescriptor;
typedef struct WaitDescriptorMethod {
    short adjustment, reserved;
    void (*activate)(void *,WaitBindDescriptor *);
} WaitDescriptorMethod;
typedef struct WaitDescriptorState {
    char unaccessed[0xC];
    WaitDescriptorMethod *table;
    char unaccessed10[0x38-0x10];
    WaitBindDescriptor *descriptor;
} WaitDescriptorState;
void func_002389A0(void *);
int func_00197A60(void *);
void func_00238AB8(void *);
void func_00197A10(void *,WaitBindDescriptor *);
void func_001979B8(WaitDescriptorState *state)
{
    func_002389A0(state);
    if(state->descriptor) {
        do {
            if(func_00197A60(state))
                break;
            func_00197A10(state,state->descriptor->next);
        } while(state->descriptor);
    }
}
void func_00197A10(void *receiver,WaitBindDescriptor *descriptor)
{
    WaitDescriptorState *state=(WaitDescriptorState *)receiver;
    if(descriptor!=state->descriptor) {
        state->descriptor=descriptor;
        if(descriptor) {
            WaitDescriptorMethod *method=&state->table[16];
            method->activate((char *)state+method->adjustment,descriptor);
        } else {
            func_00238AB8(state);
        }
    }
}
