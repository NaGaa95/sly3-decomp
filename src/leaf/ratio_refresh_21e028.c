// Refresh the two ratios of the owner's paired counters; a ratio is 0 when its total is not positive.
// SLY3_CFLAGS: -Os -G0 -ffast-math
struct RatioSelf {
    unsigned char prefix[0x124];
    float first_ratio;
    unsigned char gap128[4];
    float second_ratio;
    unsigned char gap130[0xC];
    void *owner;
};
int func_001F43F0(void *owner);
int func_001F43C8(void *owner);
int func_001F4458(void *owner);
int func_001F4430(void *owner);

void func_0021E028(struct RatioSelf *self)
{
    int total = func_001F43F0(self->owner);
    if (total > 0) {
        self->first_ratio = (float)func_001F43C8(self->owner) / (float)total;
    } else {
        self->first_ratio = 0.0f;
    }
    total = func_001F4458(self->owner);
    if (total > 0) {
        self->second_ratio = (float)func_001F4430(self->owner) / (float)total;
    } else {
        self->second_ratio = 0.0f;
    }
}
