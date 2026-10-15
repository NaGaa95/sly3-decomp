// Sly 2 reference: src/hand/func_0011D448.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
int func_0011E8B8(void);
float func_0011E940(float gMin, float gMax)
{
    if (gMin == gMax)
        return gMin;
    return gMin + (gMax - gMin) * (float)(func_0011E8B8() % 0x16A1B) * 1.078760305972537e-05f;
}
