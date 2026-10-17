// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, word2; void *function; };
struct OwnerTable { unsigned char prefix[0x388]; struct Method accept; };
struct TargetTable { unsigned char prefix[0x110]; struct Method run; };
struct Target {
    unsigned char prefix[0xC];
    struct TargetTable *methods;
    unsigned char gap10[0x2C - 0x10];
    unsigned char pad2C[3];
    unsigned char flagByte;
};
struct AsegOwner {
    unsigned char prefix[0xC];
    struct OwnerTable *methods;
    unsigned char gap10[0x1AB0 - 0x10];
    struct Target *target;
    void *aseg;
};
void func_00136908(void *aseg, void *target, float t, float svt, int flags, void *out);
void func_001E2910(struct AsegOwner *owner, qword argument)
{
    if (((int (*)(void *, int))owner->methods->accept.function)((char *)owner + owner->methods->accept.adjustment, 0x13)) {
        struct Target *target = owner->target;
        long byte = target->flagByte;
        if (!((int)byte & 1)) {
            ((void (*)(void *, qword))target->methods->run.function)((char *)target + target->methods->run.adjustment, argument);
            func_00136908(owner->aseg, owner->target, 0.0f, 1.0f, 0, 0);
        }
    }
}
