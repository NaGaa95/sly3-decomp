// Reference algorithm: src/hand/func_001C6AB8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x154]; float g1a0; char pad2[0x1C]; float g1d0, g1d4, g1d8, g1e0, g1e4; char unknown188[4]; float g1dc; };
void func_001F65F0(struct S *p);
void func_001F7FB0(struct S *p)
{
    func_001F65F0(p);
    p->g1d8 = 35.0f; //P
    p->g1dc = 35.0f; //P
    p->g1d0 = 500.0f; //P
    p->g1d4 = 250.0f; //P
    p->g1e4 = 0.6f; //P
    p->g1e0 = 0.6f; //P
    p->g1a0 = 0.75f; //P
}
