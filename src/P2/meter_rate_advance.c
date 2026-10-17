// SLY3_CFLAGS: -Os -G0
struct RateMeter {
    unsigned char prefix[0x174];
    int count;
    int maximum;
    float remainder;
};
extern float D_0036BB9C;
void func_001F4498(struct RateMeter *meter, float rate)
{
    float total = meter->remainder + rate * D_0036BB9C;
    int whole = (int)total;
    meter->remainder = total;
    if (whole != 0) {
        int remaining = meter->count - whole;
        int result = meter->maximum;
        if (remaining < result)
            result = remaining;
        if (result <= 0)
            result = 0;
        meter->count = result;
        meter->remainder = total - (float)whole;
    }
}
