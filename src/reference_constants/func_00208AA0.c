// Reference algorithm: src/hand/func_001CCA40.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct O { char pad[0xD0]; int grf; };
struct S { char pad[0x164]; int grf; };
extern char D_00475480[];
int func_0017E208(void *p, int a, int b, int c, int d, struct O **apo);
struct O *func_00208AA0(struct S *p, int n)
{
    struct O *apo[4];
    int c = func_0017E208(D_00475480, 0x401, 0x12, n, 4, apo);
    int i;
    for (i = 0; i < c; i++) {
        if (apo[i]->grf & p->grf) return apo[i];
    }
    return 0;
}
