// SLY3_CFLAGS: -Os -G0
struct BindingDefaults {
    char unknown[0xF0];
    int mask;
    int unknownF4;
    float period;
};
void func_001C7DC8(void *owner);
static __inline__ int IsSentinelPeriod(float period)
{
    return period == 1250.0f;
}
void func_001A1E58(void *receiver)
{
    struct BindingDefaults *owner = (struct BindingDefaults *)receiver;
    func_001C7DC8(owner);
    if (owner->mask == 0)
        owner->mask = 255;
    if (IsSentinelPeriod(owner->period))
        owner->period = 1000.0f;
}
