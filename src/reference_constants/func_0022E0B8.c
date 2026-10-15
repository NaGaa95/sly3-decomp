// Reference algorithm: src/hand/func_001E6728.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0xD4]; int fWrap; };
float func_0022DFB0(struct S *p);
float func_0022DFD8(struct S *p);
float func_0022E058(struct S *p, float g);
static __inline__ float GClamp(float g, float lo, float hi) { if (g < lo) return lo; if (g > hi) return hi; return g; }
float func_0022E0B8(struct S *p, float g)
{
    if (p->fWrap) return func_0022E058(p, g);
    return GClamp(g, func_0022DFB0(p), func_0022DFD8(p));
}
