// Reference algorithm: src/hand/func_001E79A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct O { char pad[0x5C]; float *ag; };
struct S { char pad[0xD8]; int c; };
struct O *func_0022F450(struct S *p, int n);
float func_0022F5B0(struct S *p)
{
    float g;
    if (p->c > 0) g = func_0022F450(p, 0)->ag[p->c - 1];
    else g = 0.0f;
    return g;
}
