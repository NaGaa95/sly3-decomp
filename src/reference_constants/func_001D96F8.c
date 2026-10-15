// Reference algorithm: src/hand/func_0017EEB8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct O { char pad[0xD4]; int nE4; };
struct S { char pad[0x30]; struct O *p30; int n34; float g38; };
extern float D_002BE7B8;
float func_0022DFD8(struct O *p);
float func_0022DFB0(struct O *p);
int func_001D96F8(struct S *p) {
    float g;
    if (p->p30->nE4) return 0;
    if (p->n34) g = func_0022DFD8(p->p30); else g = func_0022DFB0(p->p30);
    if (10.0f < __builtin_fabsf(p->g38 - g)) return 0;
    return 1;
}
