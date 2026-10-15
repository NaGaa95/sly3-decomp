// Reference algorithm: src/hand/func_001E77E8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0

struct S { char pad[0xD8]; int c; };
float func_0022DFC0(struct S *p);
float func_0022DFA0(struct S *p);
float func_0022F3F8(struct S *p)
{
    float a = func_0022DFC0(p);
    return (a - func_0022DFA0(p)) / (p->c * 10.0f);
}
