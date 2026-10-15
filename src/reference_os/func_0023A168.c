// Sly 2 reference: src/hand/func_001F0AD0.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct E { int pad[5]; float g; };
float func_0011E940(float, float);
struct E *func_0023A168(void *p, int n, struct E **ape)
{
    float sum = 0.0f;

    int i;
    for (i = 0; i < n; i++) sum += ape[i]->g;
    sum = func_0011E940(0.0f, sum);
    for (i = 0; i < n; i++) {
        sum -= ape[i]->g;
        if (sum <= 0.0f) return ape[i];
    }
    return 0;
}
