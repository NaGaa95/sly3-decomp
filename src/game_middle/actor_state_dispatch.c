// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions

struct ActorState {
    char prefix[0x19E0];
    int state;
    char gap[4];
    int secondaryState;
};

void func_00243738(void *);
void func_0024E2B8(void *);
void func_001B1798(void *);
void func_001BEF88(void *);
void func_001B88E0(void *);
void func_001C2870(void *);
void func_001B5910(void *);
void func_00140958(void *);
void func_0013A9E0(void *);
void func_001B0228(void *, float, float, float);

void func_001AA630(struct ActorState *receiver)
{
    switch (receiver->state) {
    case 4:
    case 9:
    case 17:
        func_00243738(receiver);
        break;
    default:
        func_0024E2B8(receiver);
        break;
    }

    // The first callback can change the state, so read it again.
    switch (receiver->state) {
    case 4:
        func_001B1798(receiver);
        break;
    case 9:
        func_001BEF88((char *)receiver + 0x1010);
        break;
    case 3:
        func_001B88E0((char *)receiver + 0x320);
        break;
    case 5:
        func_001C2870((char *)receiver + 0xE40);
        break;
    case 8:
        func_001B5910((char *)receiver + 0x500);
        break;
    case 7:
        func_00140958((char *)receiver + 0x1E90);
        break;
    case 23:
        func_0013A9E0((char *)receiver + 0x10D0);
        break;
    case 19:
        if (receiver->secondaryState == 7) {
            func_001B0228(receiver, 0.0f, 1.0f, 6000.0f);
        }
        break;
    }
}
