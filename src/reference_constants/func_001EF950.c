// Reference algorithm: src/hand/func_00179BA0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t; float dt; };
extern struct CLOCK D_0036BB98;
struct S { char pad[0x10]; void *p10; int pad2; void *p18; char pad3[0x14]; float f30; float f34; int n38; char pad4[4]; int n40; };
void func_002389A0(struct S *p);
int func_00254B80(void *p);
int func_00238AA8(struct S *p);
void func_001EFAB8(struct S *p, int n);
int func_00238AD0(void *p);
void func_001EF950(struct S *p) {
    int f, s;
    func_002389A0(p);
    f = func_00254B80(p->p10);
    while (!func_00238AA8(p)) {
        s = p->n38;
        switch (s) {
        case 1:
            if (f) func_001EFAB8(p, 3);
            else if (D_0036BB98.t > p->f34) func_001EFAB8(p, 0);
            break;
        case 2:
            if (f) func_001EFAB8(p, 3);
            break;
        case 0:
            if (f) func_001EFAB8(p, 3);
            else if (D_0036BB98.t > p->f30) func_001EFAB8(p, 1);
            else if (func_00238AD0(p)) { p->n40 = 0; func_001EFAB8(p, 2); }
            break;
        case 3:
            if (!f) {
                if (p->n40) func_001EFAB8(p, 1);
                else func_001EFAB8(p, 2);
            }
            break;
        }
        if (p->n38 != s) continue;
        break;
    }
}
