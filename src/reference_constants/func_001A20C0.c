// Reference algorithm: src/hand/func_00148B78.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_0036C700[];
void func_001858D0(void *a, void *b, int n, void *c, int d, int e);
void func_001A20C0(char *p, int d, int e)
{
    func_001858D0(D_0036C700, p + 0x170, 4, p + 0x16C, d, e);
}
