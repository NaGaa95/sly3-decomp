// Reference algorithm: src/hand/func_0019E110.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct C { char pad[0xD4]; int xe4; };
struct S { int a, b, c; struct C *pc; int d, e; int x18; };
float func_0022DFB0(struct C *);
float func_0022DFD8(struct C *);
void func_001BF128(struct S *p, float *ag) {
    if (p->pc->xe4) {
        ag[0] = -3.40282346638528859812e+38f;
        ag[1] = 3.40282346638528859812e+38f;
    } else if (p->x18) {
        ag[0] = func_0022DFB0(p->pc) + 35.0f;
        ag[1] = func_0022DFD8(p->pc) - 100.0f;
    } else {
        ag[0] = func_0022DFB0(p->pc) + 100.0f;
        ag[1] = func_0022DFD8(p->pc) - 35.0f;
    }
}
