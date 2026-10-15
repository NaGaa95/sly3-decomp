// Reference algorithm: src/hand/func_0014D1F8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct X { char pad[8]; float g; float g2; char pad2[8]; float af[9]; };
void func_00165570(struct X *p)
{
    unsigned int i;
    p->g = 1.0f;
    for (i = 0; i < 10; i++) {
        p->g *= p->af[i];
    }
    p->g2 = p->af[8];
}
