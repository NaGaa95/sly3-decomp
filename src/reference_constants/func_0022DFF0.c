// Reference algorithm: src/hand/func_001E6660.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0xD4]; int f; int c; float *ag; };
float func_0011EDB8(float g, float gMax);
float func_0022DFF0(struct S *p, float g)
{
    float gMin, gMax;
    if (!p->f) return g;
    gMin = p->ag[0];
    gMax = p->ag[p->c - 1];
    if (gMin <= g && g <= gMax) return g;
    return gMin + func_0011EDB8(g - gMin, gMax - gMin);
}
