// Reference algorithm: src/hand/func_00172560.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t; float dt; };
extern float D_0036BB98;
extern float D_002BE5A0;
struct T { char pad[0x100C]; float gE6C; float gE70; int pad2; int nE78; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x24]; float g38; float g3C; };
float func_0011E940(float a, float b);
void func_001A6A80(struct S *p) {
    float t = D_0036BB98;
    p->g38 = t + func_0011E940(p->pt->gE6C, p->pt->gE70);
    if (p->pt->nE78 == 1) p->g3C = D_0036BB98 + 2.0f;
    else p->g3C = 3.40282346638528859812e+38f;
}
