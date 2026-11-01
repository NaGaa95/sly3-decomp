// SLY3_CFLAGS: -Os -G0 -fno-strength-reduce
// Evaluate a value curve at its cached position: linear blend of the two neighbouring samples, or (mode != 0) a blend factor
// remapped through a 10-entry table. `blend` doubles as the result variable (that is what puts the sum in $f5). Sly 2 func_001E64C8.

struct Curve {
    unsigned char pad00[0xD0]; int mode;
    unsigned char padD4[0xDC - 0xD4]; float *values;
    unsigned char padE0[0x13C - 0xE0]; float table[10];
};
int func_0022F198(struct Curve *curve, float *offset, float *length);
void func_0022D950(struct Curve *curve, int index);
static __inline__ float Lerp(float a, float b, float t)
{
    return (1.0f - t) * a + t * b;
}
float func_0022DE50(struct Curve *curve)
{
    float span[2];
    float blend;
    int index = func_0022F198(curve, &span[0], &span[1]);
    if (curve->mode == 0) {
        float fraction = span[0] / span[1];
        blend = Lerp(curve->values[index], curve->values[index + 1], fraction);
    } else {
        int i;
        func_0022D950(curve, index);
        for (i = 1; i < 10; i++)
            if (span[0] < curve->table[i])
                break;
        i--;
        blend = (span[0] - curve->table[i]) / (curve->table[i + 1] - curve->table[i]);
        blend = ((float)i + blend) * 0.1f;
        blend = Lerp(curve->values[index], curve->values[index + 1], blend);
    }
    return blend;
}
