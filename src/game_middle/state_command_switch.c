// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct StateOwner {
    unsigned char prefix[0x248];
    float offset;
    unsigned char gap24C[0x50C - 0x24C];
    int contextMode;
    unsigned char gap510[0x1154 - 0x510];
    float timestamp;
    float stamp;
    unsigned char gap115C[0x11BC - 0x115C];
    int mode;
    unsigned char gap11C0[0x1520 - 0x11C0];
    int state;
};
struct StateCommand {
    unsigned char prefix[8];
    float value;
    unsigned char gapC[0x54 - 0xC];
    int cleared;
    unsigned char gap58[0x6C - 0x58];
    int flags;
};
extern float D_0036BB98;
void func_00153D40(void *owner, void *command);
void func_00272E68(void *handler, void *command);
void func_001DEE28(struct StateOwner *owner, struct StateCommand *command)
{
    if (owner->state != 0 && owner->state != 0x11) {
        if (owner->contextMode)
            owner->timestamp = D_0036BB98;
    }
    func_00153D40(owner, command);
    switch (owner->state) {
    case 0xC:
        if (owner->mode == 4)
            command->flags |= 1;
        break;
    case 3:
    case 0xA:
    case 0xD:
        command->flags |= 1;
        break;
    case 0x10:
        func_00272E68((char *)owner + 0x18E0, command);
        break;
    case 0x16:
        command->value = owner->offset + owner->stamp;
        command->cleared = 0;
        command->flags &= ~4;
        break;
    }
}
