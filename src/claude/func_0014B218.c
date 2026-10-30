// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x20]; qword q; };
void func_0014B218(struct S *s, qword *a, int *b)
{
    if (a)
        *a = s->q;
    if (b) {
        b[2] = 0;
        b[1] = 0;
        b[0] = 0;
    }
}
