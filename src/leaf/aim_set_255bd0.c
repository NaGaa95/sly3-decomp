// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
struct AimTarget {
    unsigned char prefix[0x30];
    int mode;
    unsigned char gap34[0xC];
    QWORD value;
};
struct AimController {
    unsigned char prefix[0x18];
    struct AimTarget *target;
    unsigned char gap1C[0x14];
    int state;
};
struct AimOwner {
    unsigned char prefix[0x10D8];
    int mode;
    unsigned char gap10DC[4];
    QWORD value;
};
void *func_002387A8(void *list, int key);
void func_00255BD0(struct AimOwner *owner, int mode, QWORD value)
{
    struct AimController *controller;
    struct AimTarget *target;
    owner->mode = mode;
    owner->value = value;
    controller = (struct AimController *)func_002387A8((char *)owner + 0x29C, 0xC8);
    if (controller && owner->mode && controller->state == 0xE) {
        target = controller->target;
        target->mode = owner->mode;
        target->value = owner->value;
    }
}
