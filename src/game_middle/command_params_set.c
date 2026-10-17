// SLY3_CFLAGS: -Os -G0
struct Clock { float now, step; };
extern struct Clock D_0036BB98;
struct ParamReceiver {
    unsigned char prefix[0x50C];
    int contextMode;
    unsigned char gap510[0x1154 - 0x510];
    float timestamp;
    unsigned char gap1158[0x1470 - 0x1158];
    int state;
};
struct ParamCommand {
    unsigned char prefix[0x30];
    float first;
    float second;
};
void func_00153D40(void *receiver, void *command);
void func_001EA298(struct ParamReceiver *receiver, struct ParamCommand *command)
{
    if (receiver->state && receiver->contextMode)
        receiver->timestamp = D_0036BB98.now;
    func_00153D40(receiver, command);
    command->first = 0.22f;
    command->second = 100.0f;
}
