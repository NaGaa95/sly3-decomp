// Reference algorithm: src/hand/func_001BC050.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x1C4]; char dl[0x24]; int f1e8; };
int func_0011C330(void);
void func_001C7068(void *pdl, int ib);
void func_001C71B0(struct S *p)
{
    if (func_0011C330() < 2) func_001C7068(p, 5);
}
