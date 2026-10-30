// SLY3_CFLAGS: -Os -G0
typedef struct { float x, y, z; } VEC3;
struct S0 { int a, b, c; int d; int e; int f; char pad[0x50-0x18]; VEC3 v50; int p5c; VEC3 v60; int p6c; VEC3 v70; };
/* .data table at 0x00344F28 (not in symbol_addrs); placed by its bytes */
static int D_00344F28[10][3] = {
    { 0x300, 0x265, 0x184c },
    { 0x300, 0x266, 0x1850 },
    { 0x300, 0x267, 0x1858 },
    { 0x300, 0x268, 0x185c },
    { 0x300, 0x269, 0x1860 },
    { 0x300, 0x26a, 0x1864 },
    { 0x300, 0x26b, 0x1868 },
    { 0x300, 0x26d, 0x186c },
    { 0x300, 0x26e, 0x1870 },
    { 0x300, 0x26c, 0x1874 }
};
void func_001C8970(int, int, void *, int);
static inline void SetV(VEC3 *v, float x, float y, float z) { v->x = x; v->y = y; v->z = z; }
void func_0017E760(struct S0 *p, int a, int b, int c)
{
    p->a = a;
    p->b = b;
    p->c = c;
    SetV(&p->v60, 10.0f, 0.0f, 15.0f);
    SetV(&p->v70, -1500.0f, 0.0f, -500.0f);
    SetV(&p->v50, -35.0f, 0.0f, 0.0f);
    func_001C8970(p->a, 10, D_00344F28, 0);
    p->d = -1;
    p->f = -1;
}
