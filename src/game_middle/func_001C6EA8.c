// SLY3_CFLAGS: -Os -G0
struct S { int x0; char pad[0x1C0]; int x1C4; };
extern char D_00317EB8[], D_00317EF8[];
void func_001C70D8(struct S *p, void *b);
void func_001C71B0(struct S *p);
void *func_0025E070(int id);
void func_001C7130(struct S *p, void *b, int n, int m);
void func_001C6F30(struct S *p);
void func_001C6EA8(struct S *p)
{
    p->x0 = 0;
    p->x1C4 = 0;
    func_001C70D8(p, D_00317EB8);
    func_001C70D8(p, D_00317EF8);
    func_001C71B0(p);
    func_001C7130(p, func_0025E070(0x23), 0x1A8, 0x23);
    func_001C6F30(p);
}
