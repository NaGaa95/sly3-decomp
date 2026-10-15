// Store the selected mode and parameter, initialize its timestamp, and reset the mode-specific resource.
// Reference algorithm: src/hand/func_001DA950.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern struct CLOCK { float a[16]; } D_0036BB9C;
extern float D_00326044, D_0034903C;
struct S { char p0[0x40]; int n30; float g34; int n38; };
void *func_002459F8(int n);
void func_00244F08(void *p, int n);
void func_0021ED28(struct S *p, int n, int m) {
    p->n38 = m;
    p->n30 = n;
    switch (n) {
    case -1:
        p->g34 = -10.0f;
        break;
    case 0:
        p->g34 = D_00326044;
        func_00244F08(func_002459F8(0x29), 0);
        break;
    case 1:
    default:
        p->g34 = D_0036BB9C.a[15] + D_0034903C;
        func_00244F08(func_002459F8(0x36), 0);
        break;
    }
}
