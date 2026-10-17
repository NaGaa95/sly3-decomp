// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int SettleVector __attribute__((mode(TI)));
struct SettleTarget {
    unsigned char prefix[0xE0];
    float endTime;
};
struct SettleParent {
    unsigned char prefix[0x260];
    SettleVector offset;
};
struct SettleBlend {
    unsigned char prefix[0x10];
    SettleParent *parent;
    unsigned char gap14[4];
    SettleTarget *target;
    unsigned char gap1C[0x30 - 0x1C];
    unsigned char point[0x50 - 0x30];
    int mode;
};
extern "C" {
extern float D_0036BB98;
extern SettleVector D_00317560;
void func_002389A0(void *receiver);
int func_00238AD0(void *receiver);
void func_001D9EF0(void *receiver, int state, SettleVector vector);
SettleVector func_001C03A0(void *owner, void *point, float duration);
void func_00132930(void *target, SettleVector position);
}
static inline SettleVector AddSettleVectors(SettleVector a, SettleVector b)
{
    SettleVector sum;
    asm("vadd.xyzw %0,%1,%2" : "=j"(sum) : "j"(a), "j"(b));
    return sum;
}
extern "C" void func_001D9D58(SettleBlend *blend)
{
    int mode;
    func_002389A0(blend);
    mode = blend->mode;
    do {
        mode = blend->mode;
        switch (mode) {
        case 0:
            if (func_00238AD0(blend))
                func_001D9EF0(blend, -1, D_00317560);
            break;
        case 1:
            func_001D9EF0(blend, -1, D_00317560);
            break;
        }
    } while (mode != blend->mode);
    if (mode == 0) {
        SettleTarget *target = blend->target;
        float low = 0.0f, high = 0.7f;
        float remaining = target->endTime - D_0036BB98;
        if (remaining < low)
            remaining = low;
        else if (high < remaining)
            remaining = high;
        func_00132930(target, AddSettleVectors(func_001C03A0(blend->parent, blend->point, remaining), blend->parent->offset));
    }
}
