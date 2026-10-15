// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct StateReceiver {
    char prefix[0x50C];
    int context_mode;
    char to_time[0x1154 - 0x510];
    float timestamp;
    char to_state[0x1470 - 0x1158];
    int state;
};
struct Command {
    char prefix[0x6C];
    unsigned int flags;
};

extern float D_0036BB98;
int func_00154518(void *receiver, int mode);
int func_001BD830(void *context, int mode);
int func_001B5D08(void *context, int mode);
void func_00153D40(void *receiver, void *command);

int func_001F0F70(struct StateReceiver *receiver, int mode)
{
    if (!func_00154518(receiver, mode))
        return 0;
    switch (receiver->state) {
    case 5:
        if (!func_001BD830((char *)receiver + 0x320, mode))
            return 0;
        break;
    case 6:
        if (!func_001B5D08((char *)receiver + 0x500, mode))
            return 0;
        break;
    case 7:
        return 0;
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 8:
        break;
    default:
        return 0;
    }
    return mode == 2;
}

void func_001F1008(struct StateReceiver *receiver, struct Command *command)
{
    if (receiver->state != 0 && receiver->context_mode != 0)
        receiver->timestamp = D_0036BB98;
    func_00153D40(receiver, command);
    switch (receiver->state) {
    case 3:
    case 4:
        command->flags |= 1;
        break;
    }
}
