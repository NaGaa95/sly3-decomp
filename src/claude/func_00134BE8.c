// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S { char pad[0x30]; int mode; };
float func_00134BE8(struct S *ps, float g)
{
    switch (ps->mode) {
    case 1:
        return g;
    case 2:
        return 1.0f;
    case 3:
    case 5:
        return 1.0f - g;
    case 0:
    case 4:
    default:
        return 0.0f;
    }
}
/* Next .rodata item of the original unit (the FLT_MAX literal read by func_001355C8); it follows the jump table. */
const float D_0031F858 = 3.40282346638528859812e+38f;
