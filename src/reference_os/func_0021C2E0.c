// Sly 2 reference: src/hand/func_001D7E80.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct X { short a; signed char b; char c; unsigned short h; };
struct T { struct X *px; int n; };
extern int D_00348BB0[];
void func_0021C208(void *a, void *b, struct T *pt);
char *func_0021C2E0(void *a, void *b, char *pb) {
    struct T t;
    func_0021C208(a, b, &t);
    return pb + (t.px->h + t.n * D_00348BB0[t.px->b]);
}
