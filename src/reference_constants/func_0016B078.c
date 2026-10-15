// Reference algorithm: src/hand/func_001510D8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { int pad[10]; float g18; char pad2[0xAC - 0x1C]; float gAC; };
int func_0011E9F0(float a, float b, float eps);
int func_0016B078(struct S *p)
{
    int f = 0;
    if (p->g18 < 0.0f || func_0011E9F0(p->gAC, p->g18, 0.01f))
        f = 1;
    return f;
}
