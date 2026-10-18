// SLY3_CFLAGS: -Os -G0
struct ScalarLimits {
    unsigned char prefix0[0x154];
    int word154;
    unsigned char gap158[0x18C - 0x158];
    float range;
    unsigned char gap190[0x1A0 - 0x190];
    float lowA;
    float lowB;
    float lowC;
    float high;
};
void func_001F65F0(struct ScalarLimits *receiver);
static inline void SetLimits(struct ScalarLimits *self, float range, float lowA, float lowB, float lowC, float high)
{
    self->range = range;
    self->high = high;
    self->lowA = lowA;
    self->lowB = lowB;
    self->lowC = lowC;
}
void func_001F9278(struct ScalarLimits *receiver)
{
    func_001F65F0(receiver);
    SetLimits(receiver, 3000.0f, 25.0f, 50.0f, 5.0f, 15.0f);
    receiver->word154 = 0;
}
