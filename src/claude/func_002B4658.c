// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
struct S { int x0; unsigned int lo : 31; unsigned int hi : 1; };
extern struct { unsigned short x; } D_0036B138;
extern struct { int x; } D_004793C4;
extern int D_0036AE3C;
void func_002B4588(struct S *, int *);
struct S *func_002B4658(struct S *s)
{
    s->x0 = 0;
    s->hi = D_0036B138.x;
    if (!D_004793C4.x)
        func_002B4588(s, &D_0036AE3C);
    return s;
}
