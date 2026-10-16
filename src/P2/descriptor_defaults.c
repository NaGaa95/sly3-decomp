// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct DescriptorDefaults {
    char prefix[0x3C];
    unsigned int changed;
    char gap40[0x90];
    int selection;
    char gapD4[0x38];
    float distance;
    int enabled, pending;
};
void func_0028FD70(void *receiver);

void func_001FEA08(void *receiver)
{
    struct DescriptorDefaults *property = receiver;
    unsigned int changed;
    func_0028FD70(receiver);
    property->enabled = 1;
    property->distance = 100.0f;
    property->selection = -1;
    property->pending = 0;
    changed = property->changed;
    if ((changed ^ 1) & 1)
        *(unsigned int *)changed |= 2;
    else
        property->changed = changed | 2;
}
