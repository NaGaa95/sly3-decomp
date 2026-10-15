// Reference algorithm: src/hand/func_00224590.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x30]; int x; };
int func_00134AB8(struct S *p)
{
    switch (p->x) { case 1: case 2: case 3: return 1; }
    return 0;
}
