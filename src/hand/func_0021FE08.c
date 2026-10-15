// Initialize timestamp and state fields, and clear all 67 pairs of entry identifiers to -1.
// Reference algorithm: src/hand/func_001DB820.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern struct CLOCK { float a[16]; } D_0036BB9C;
struct P { int a, b; };
struct S { char p0[0x50]; int n40; float g44; int pad; struct P ap[67]; char p1[0x280-0x274]; int n25C, n260, n264; };
void func_0021FE08(struct S *p) {
    unsigned int i;
    p->n40 = -1;
    p->g44 = D_0036BB9C.a[15];
    p->n25C = -1;
    p->n260 = -1;
    p->n264 = -1;
    for (i = 0; i < 67; i++) {
        p->ap[i].a = -1;
        p->ap[i].b = -1;
    }
}
