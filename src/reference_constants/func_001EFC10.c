// Reference algorithm: src/hand/func_00179E80.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t; float dt; };
extern struct CLOCK D_0036BB98;
struct T { char pad[0x308]; float g2CC; float g2D0; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x1C]; float g30; };
float func_0011E940(float a, float b);
void func_001EFC10(struct S *p) {
    if (p->g30 < 3.40282346638528859812e+38f) return;
    if (p->pt->g2CC == 3.40282346638528859812e+38f) p->g30 = 3.40282346638528859812e+38f;
    else { float t = D_0036BB98.t; p->g30 = t + func_0011E940(p->pt->g2CC, p->pt->g2D0); }
}
