// Refresh the controller target from its parameter descriptor and, for target-driven parameter kinds, release the target attachment or restart the controller depending on the owner state.
// SLY3_CFLAGS: -Os -G0
struct Target;
struct Descriptor {
    unsigned char type;
    unsigned char pad01[3];
    int index;
};
struct Owner {
    unsigned char opaque00[0x58];
    struct Target *object;
    unsigned char opaque5C[0xA8 - 0x5C];
    int state;
};
struct Target {
    unsigned char opaque000[0x1108];
    void *attachment;
};
struct Controller {
    unsigned char opaque00[0x14];
    struct Owner *owner;
    unsigned char opaque18[8];
    struct Target *override;
    struct Target *preferred;
    struct Target *current;
    unsigned char opaque2C[8];
    struct Descriptor *descriptor;
    unsigned char opaque38[0x170 - 0x38];
    int locked;
};
void func_0022B238(struct Controller *self, int mode);
struct Target *func_00226770(struct Controller *self, int index);
int func_0013B500(void *object, int kind);
void func_00172D10(void *attachment, int value);

static inline struct Target *PickTarget(struct Controller *self)
{
    if (self->preferred) return self->preferred;
    if (self->override) return self->override;
    return self->owner->object;
}

void func_00226BE0(struct Controller *self)
{
    struct Target *target = 0;
    struct Descriptor *descriptor;
    func_0022B238(self, 0);
    descriptor = self->descriptor;
    if (descriptor->type) {
        if (descriptor->index != -1) {
            target = func_00226770(self, descriptor->index);
        } else {
            target = PickTarget(self);
        }
    }
    self->current = target;
    if (self->locked == 0 && target && func_0013B500(target, 0x34)) {
        unsigned char kindIndex = descriptor->type - 0x16;
        switch (kindIndex) {
        case 0x00:
        case 0x10: case 0x11: case 0x12:
        case 0x14: case 0x15: case 0x16: case 0x17: case 0x18:
        case 0x1A:
        case 0x1D: case 0x1E: case 0x1F: case 0x20: case 0x21:
        case 0x46: case 0x47: case 0x48:
        case 0x4E: case 0x4F: case 0x50: case 0x51:
        case 0x55: case 0x56: case 0x57: case 0x58:
        case 0x5D: case 0x5E:
            switch (self->owner->state) {
            case 0:
                if (target->attachment) func_00172D10(target->attachment, -1);
                break;
            case 2:
                func_0022B238(self, 1);
                break;
            }
            break;
        }
    }
}
