// Reference algorithm: src/hand/func_00179EF8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t; float dt; };
extern struct CLOCK D_0036BB98;
struct T { char pad[0x310]; float g2D4; float g2D8; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x20]; float g34; };
float func_0011E940(float a, float b);
void func_001EFC88(struct S *p) {
    if (p->g34 < 3.40282346638528859812e+38f) return;
    if (p->pt->g2D4 == 3.40282346638528859812e+38f) p->g34 = 3.40282346638528859812e+38f;
    else { float t = D_0036BB98.t; p->g34 = t + func_0011E940(p->pt->g2D4, p->pt->g2D8); }
}
