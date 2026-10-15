// Original A1 is the nullable owner passed unchanged to the base initializer.
// Reference algorithm: src/hand/func_001BBEA8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0xD8]; int f; };
void func_001FC968(void *receiver, void *owner);
void func_001E50B0(struct S *p, int n);
void func_0023EBF8(struct S *p, int n);
void func_0023EC98(struct S *p, int n);
void func_001E6058(struct S *p, void *owner)
{
    func_001FC968(p, owner);
    func_001E50B0(p, 0x6DA);
    if (p->f) {
        func_0023EBF8(p, 1);
        func_0023EC98(p, 1);
    }
}
