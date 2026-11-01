// SLY3_CFLAGS: -O2 -G0
extern char D_00474FF0[];
extern float D_00341FF0[2];
float func_002483D8(void *clock);
struct BlendOwner {
    unsigned char prefix[0x198];
    float rise;
    float fall;
};
static inline float Lerp(float a, float b, float t) { return (1.0f - t) * a + t * b; }
float func_0020ABA0(struct BlendOwner *owner, float *time)
{
    float now = func_002483D8(D_00474FF0);
    float d;
    if (now < *time)
        d = (*time - now) / owner->rise;
    else
        d = (now - *time) / owner->fall;
    return Lerp(D_00341FF0[0], D_00341FF0[1], 1.0f - d);
}
