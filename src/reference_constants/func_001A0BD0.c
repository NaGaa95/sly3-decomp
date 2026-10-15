// Reference algorithm: src/hand/func_00182FE8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0xD4]; int x; };
float func_0022DFB0(struct S *p);
float func_0022DFD8(struct S *p);
int func_001A0BD0(struct S *p, float *pg)
{
    if (p->x) {
        pg[0] = func_0022DFB0(p);
        pg[1] = func_0022DFD8(p);
        return 1;
    }
    return 0;
}
