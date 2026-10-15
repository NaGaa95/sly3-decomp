// Build and release two references to the owner's paired numeric fields from explicit reference inputs, using the original 16-bit reference tag.
// Reference algorithm: src/hand/func_0020A058.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef struct { short tagk; short pad; int tag; } CRef;
void func_0024B330(CRef *pr, CRef *a, int b, int c, void *d, void *e);
void func_0012B3B0(CRef *pd, CRef *ps);
void func_0012BC20(CRef *pr);
struct S { char pad[0x1104]; int a; int b; char pad2[0x1118 - 0x110C]; int c; int d; };
void func_00255B28(struct S *p, CRef *x, CRef *y)
{
    CRef r;
    CRef t;
    r.tagk = -1;
    func_0024B330(&t, x, 0x2002, 4, &p->a, &p->b);
    func_0012B3B0(&r, &t);
    func_0012BC20(&t);
    func_0024B330(&t, y, 0x2002, 4, &p->c, &p->d);
    func_0012B3B0(&r, &t);
    func_0012BC20(&t);
    func_0012BC20(&r);
}
