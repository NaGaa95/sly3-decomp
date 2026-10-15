// Original A1 is the nullable owner passed unchanged to the base initializer.
// Reference algorithm: src/hand/func_00185BF8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x144]; float g; };
extern float D_00320E50;
void func_001FC968(void *receiver, void *owner);
void func_001697A0(struct S *p, void *owner)
{
    func_001FC968(p, owner);
    p->g = D_00320E50;
}
