// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
struct S { short x0; short x2; int x4; unsigned int lo : 31; unsigned int hi : 1; };
extern struct { unsigned short x; } D_0036B138;
extern struct { int x; } D_004793C4;
extern int D_0036AE00;
void func_002B3A48(struct S *, int *);
struct S *func_002B3B18(struct S *s)
{
    s->x0 = -1;
    s->x2 = 0;
    s->hi = D_0036B138.x;
    if (!D_004793C4.x)
        func_002B3A48(s, &D_0036AE00);
    return s;
}
