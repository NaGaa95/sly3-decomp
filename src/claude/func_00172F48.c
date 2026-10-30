// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VEntry { short delta; short pad; int (*fn)(void *); };
struct A { char pad[0x24]; int id; };
struct B { char pad[0x14]; int id; };
struct W { char pad[0xC]; struct VEntry *table; char pad2[0x113C - 0x10]; struct B *pb; struct A *pa; };
struct R { int x0; int id; };
struct S { char pad[0x4C]; struct W *pw; void *p50; };
int func_001733F8(struct S *p);
int func_001733B8(struct S *p);
struct R *func_00173408(struct S *p);
int func_00172F48(struct S *p)
{
    struct W *pw;
    int f;
    int a;
    int b;
    int r0;
    if (!p->p50)
        return 0;
    pw = p->pw;
    f = 0;
    a = 0;
    if (pw->pa)
        a = pw->pa->id;
    b = 0;
    if (pw->pb)
        b = pw->pb->id;
    switch (pw->table[100].fn((char *)pw + pw->table[100].delta)) {
    case 0:
        r0 = func_001733F8(p);
        if (a && a == r0)
            f = 1;
        break;
    case 1:
        r0 = func_001733B8(p);
        if (b && b == r0)
            f = 1;
        break;
    case 11: {
        struct R *r = func_00173408(p);
        if (b && r && b == r->id)
            f = 1;
        break;
    }
    }
    return f;

}
