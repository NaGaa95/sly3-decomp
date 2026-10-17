// SLY3_CFLAGS: -Os -G0
struct Method { short adjustment, word2; void *function; };
struct MethodTable { unsigned char prefix[0x110]; struct Method run; };
struct Target {
    unsigned char prefix[0xC];
    struct MethodTable *methods;
    unsigned char gap10[0x2C - 0x10];
    unsigned char pad2C[3];
    unsigned char flagByte;
};
struct AsegOwner {
    unsigned char prefix[0x1AB8];
    struct Target *target;
    void *aseg;
};
void func_00136908(void *aseg, void *target, float t, float svt, int flags, void *out);
void func_001E29B0(struct AsegOwner *owner)
{
    struct Target *target = owner->target;
    long byte = target->flagByte;
    if (!((int)byte & 1)) {
        ((void (*)(void *))target->methods->run.function)((char *)target + target->methods->run.adjustment);
        func_00136908(owner->aseg, owner->target, 0.0f, 1.0f, 0, 0);
    }
}
