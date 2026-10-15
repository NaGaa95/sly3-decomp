// Reference algorithm: src/hand/func_001C02D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct T { char pad[0xD8]; int ne8; char pad2[8]; int nf4; };
int func_001EC300(void *p, int a, int b, int c, int d);
void func_0022DB08(struct T *pt);
int func_001EC688(char *p, int a, int b, struct T *pt)
{
    int n = func_001EC300(p + 0xD0, a, b, 0x10, pt->nf4);
    if (n < 2) return 0;
    pt->ne8 = n;
    func_0022DB08(pt);
    return 1;
}
