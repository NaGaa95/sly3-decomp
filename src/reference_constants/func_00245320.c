// Reference algorithm: src/hand/func_001FB658.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x5C]; unsigned short fl; };
void func_00245370(struct S *);
void func_002453D8(struct S *);
void func_00245320(struct S *p, unsigned short m, unsigned short v)
{
    p->fl = (p->fl & ~m) | (v & m);
    if (p->fl) func_00245370(p); else func_002453D8(p);
}
