// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
extern char D_00355C50[] __asm__("D_00355CA0-0x50"); /* 0x355C50 has no symbol_addrs entry yet */
struct S { int a, b, n8; char pad[0x1C - 0xC]; void *p1C; int x20; int x24; };
void func_00169C90(struct S *p, int a, int b);
struct S *func_0016C608(struct S *p, int a, int b, int c, int d)
{
    func_00169C90(p, a, b);
    p->x20 = c;
    p->p1C = D_00355C50;
    p->x24 = d;
    p->n8 = 11;
    return p;
}
