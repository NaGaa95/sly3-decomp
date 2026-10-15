// Reference algorithm: src/hand/func_0017A5B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t; float dt; };
extern struct CLOCK D_0036BB98;
struct U { int k; int pad; void *p8; };
struct T { char pad[0x101C]; float gE7C; float gE80; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x2C]; struct U *p40; char pad3[0xC]; int n50; float g54; float g58; };
void func_00239CE8(void *p, int n);
float func_0011E940(float a, float b);
void func_0016D480(struct S *p, int n) {
    if (n == p->n50) return;
    p->n50 = n;
    p->g54 = n;
    switch (n) {
    case 0:
        if (p->p40->k == 1) func_00239CE8(p->p40->p8, 0x61);
        { float t = D_0036BB98.t; p->g58 = t + func_0011E940(p->pt->gE7C, p->pt->gE80); }
        break;
    case 1:
        if (p->p40->k == n) func_00239CE8(p->p40->p8, 0x60);
        break;
    }
}
