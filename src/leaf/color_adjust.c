// Reference algorithm: Sly 2 func_001ED278; actual Sly 3 flag and helpers.
// SLY3_CFLAGS: -Os -G0
struct ClutPixel { unsigned char red, green, blue, alpha; };
extern unsigned int D_0036DBEC;
void func_0011F230(struct ClutPixel *, float *);
void func_002369D8(float *);
void func_0011F288(float *, int, struct ClutPixel *);

typedef char ColorWidth[(sizeof(struct ClutPixel) == 4) ? 1 : -1];

void func_00236908(struct ClutPixel *color)
{
    float work[4] __attribute__((aligned(16)));
    struct ClutPixel copy;
    if (((int)D_0036DBEC >> 1) & 1) {
        copy = *color;
        func_0011F230(&copy, work);
        func_002369D8(work);
        func_0011F288(work, color->alpha, color);
    }
}
