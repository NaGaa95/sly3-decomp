// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Push a qword onto a 16-entry list (count at 0x88, array at 0x8C).
typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x88]; int c; qword *a; };
void func_00198A20(struct S *p, qword x)
{
    int i = p->c;
    register int n __asm__("$3") = i + 1; /* the one register pin */
    if (i < 16) {
        p->c = n;
        p->a[i] = x;
    }
}
