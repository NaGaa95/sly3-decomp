// Reference algorithm: src/hand/func_00156C80.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x47A8]; int a; int b; };
void func_00173E48(int n, qword q, int c, int d);
void func_00173EE8(struct S *p, int k, qword q, int c, int d)
{
    int n;
    switch (k) {
    case 0: n = p->a; break;
    case 1: n = p->b; break;
    default: n = 0; break;
    }
    func_00173E48(n, q, c, d);
}
