// SLY3_CFLAGS: -Os -G0
struct LM { float gMin; float gMax; };
extern float D_00325840[3];
extern struct LM D_00341FF0;
struct GainOwner {
    unsigned char prefix[0x400];
    void *target;
    float phase;
    int full;
};
void func_00261580(void *receiver, int event, float gain);
static inline float GClamp(float g, float gMin, float gMax)
{
    float result;
    if (g < gMin)
        result = gMin;
    else if (gMax < g)
        result = gMax;
    else
        result = g;
    return result;
}
void func_00207880(struct GainOwner *self)
{
    if (self->target) {
        float gain;
        if (self->full) {
            gain = 1.0f;
        } else {
            float t = self->phase;
            gain = GClamp(D_00325840[0] + t * (D_00325840[1] + t * D_00325840[2]), D_00341FF0.gMin, D_00341FF0.gMax);
        }
        func_00261580(self->target, 0x37C, gain);
    }
}
