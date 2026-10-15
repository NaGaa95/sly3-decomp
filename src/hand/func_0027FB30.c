// Deserialize the leading 64-byte record and a counted array of further 64-byte records into the original Sly 3 layout.
// Reference algorithm: src/hand/func_002282B0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct M { int cb; int a; };
struct R { char bytes[0x40]; };
struct S { char pad[0x130]; struct R x; int c; struct R *a; };
void func_0027F158(struct S *p, void *q);
void func_00119948(void *q, struct R *p);
int func_00118FF8(void *q);
struct R *func_001D2470(struct M *pm);
void func_0027FB30(struct S *p, void *q)
{
    int i = 0;
    int n;
    struct M m;
    func_0027F158(p, q);
    func_00119948(q, &p->x);
    n = func_00118FF8(q);
    m.a = 0x10;
    m.cb = n * sizeof(struct R);
    p->c = n;
    p->a = func_001D2470(&m);
    for (; i < p->c; i++) func_00119948(q, &p->a[i]);
}
