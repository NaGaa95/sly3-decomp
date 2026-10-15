#include "heap_frame_api.h"
// Sly 2 reference: src/hand/func_00170730.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct B {
    int a[12];
};
struct MK {
    int a;
};
extern int D_00474F4C, D_00474F48;
extern int D_0036BD40;
void func_0018C750(struct B *pb);
void func_001744E8(struct B *pb, int n);
void func_001746C0(struct B *pb);
int func_002362D0(int a, void *p, struct B *pb);
void func_0018CA08(struct B *pb, int a, int b, int c);
void func_0018CCC0(struct B *pb, int a, int b);
void func_0018C798(struct B *pb);
void func_001748B8(struct B *pb);
void func_00174550(struct B *pb, int a, int *pn);
void func_00195760(int a, int b);
void func_00196E08(void *p) {
    struct B b;
    struct MK mk;
    int n;
    func_0018C750(&b);
    func_001D2770(&mk);
    func_001744E8(&b, ((D_00474F4C * 3 + D_00474F48) << 3) | 4);
    func_001746C0(&b);
    if (func_002362D0(1, p, &b)) {
        func_0018CA08(&b, 0, 1, 0xE);
        func_0018CCC0(&b, 0x3F, 0);
        func_0018CCC0(&b, 0x61, 0);
        func_0018C798(&b);
        func_001748B8(&b);
        func_00174550(&b, 0, &n);
        func_00195760(D_0036BD40, n);
    }
    func_001D2798(&mk, 2);
}
