// Sly 2 reference: src/hand/func_002159E0.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct S { int a; int k; };
void func_00265E38(struct S *p, int a, int b, int c);
void func_002666A0(struct S *p, int a, int b, int c);
void func_00266A00(struct S *p, int a, int b, int c);
void func_00264818(struct S *p, int a, int b, int c)
{
    switch (p->k) {
    case 3:
        func_00265E38(p, a, b, c);
        break;
    case 1:
        func_002666A0(p, a, b, c);
        break;
    case 6:
    case 7:
        func_00266A00(p, a, b, c);
        break;
    case 2:
    case 4:
    case 5:
    case 8:
        break;
    }
}
