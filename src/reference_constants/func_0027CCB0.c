// Reference algorithm: src/hand/func_00225AA8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x1DC]; int x; };
void func_001F3BF8(struct S *p);
void func_0027D608(struct S *p, int a);
void func_0027CCB0(struct S *p)
{
    func_001F3BF8(p);
    if (p->x) { p->x = 0; func_0027D608(p, 1); }
}
