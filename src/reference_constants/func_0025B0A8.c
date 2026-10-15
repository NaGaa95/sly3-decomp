// Reference algorithm: src/hand/func_0020E2B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct O { char pad[0xA8]; int nB8; char p2[0xC]; int nC8; };
struct S { char pad[0x45E0]; int n; };
int func_0017E208(struct S *p, int a, int b, int c, int cMax, struct O **apo);
void func_001C9198(struct O *o, int n);
void func_0025B0A8(struct S *p)
{
    struct O *apo[16];
    int c = func_0017E208(p, 5, 0x30, 0, 16, apo);
    int nMax = 0;
    struct O *poBest = 0;
    int i;
    for (i = 0; i < c; i++) {
        if (apo[i]->nB8 > nMax) {
            nMax = apo[i]->nB8;
            poBest = apo[i];
        }
    }
    if (poBest) {
        p->n = poBest->nC8;
        func_001C9198(poBest, 0xFF);
    }
}
