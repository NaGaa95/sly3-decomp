// SLY3_AS: gnu-2.9
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ActorState {
    char prefix[0x1520];
    int state;
};

void func_00243738(void);
void func_0024E2B8(void *);
void func_001B88E0(void *);
void func_001B5910(void *);
void func_001C2870(void *);
void func_001DF518(void *);
void func_001BEF88(void *);
void func_001E4250(void *);

void func_001DEF10(struct ActorState *receiver)
{
    switch (receiver->state) {
    case 21:
    case 22:
        func_00243738();
        break;
    default:
        func_0024E2B8(receiver);
        break;
    }

    // The first callback can change the state, so read it again.
    switch (receiver->state) {
    case 2:
        func_001B88E0((char *)receiver + 0x320);
        break;
    case 14:
        func_001B5910((char *)receiver + 0x500);
        break;
    case 15:
        func_001C2870((char *)receiver + 0xE40);
        break;
    case 3:
        func_001DF518(receiver);
        break;
    case 21:
        func_001BEF88((char *)receiver + 0x1010);
        break;
    case 22:
        func_001E4250(receiver);
        break;
    }
}
