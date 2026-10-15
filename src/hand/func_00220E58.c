// Initialize the current mode, timestamp, and three selection identifiers.
// Reference algorithm: src/hand/func_001DCD08.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern struct CLOCK { float a[16]; } D_0036BB9C;
struct S { char p0[0x50]; int n40; float g44; char p1[0x11C-0x48]; int n11C, n120, n124; };
void func_00220E58(struct S *p) {
    p->n40 = -1; //P
    p->g44 = D_0036BB9C.a[15]; //P
    p->n11C = -1; //P
    p->n120 = -1; //P
    p->n124 = -1; //P
}
