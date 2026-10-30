// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VEntry { short delta; short pad; int (*fn)(void *); };
struct A { char pad[0x24]; int id; };
struct B { char pad[0x14]; int id; };
struct R { int x0; int id; };
struct W { char pad[0xC]; struct VEntry *table; char pad2[0x1134 - 0x10]; int id1134; char pad3[4]; struct B *pb; struct A *pa;
           char pad4[0x1680 - 0x1144]; struct R r1680; char pad5[0x1770 - 0x1688]; struct R r1770; char pad6[0x1C90 - 0x1778]; struct R r1C90; };
struct S { char pad[0x4C]; struct W *pw; };
int func_0013B868(struct W *pw);
int func_00173068(struct S *p)
{
    struct W *pw;
    int a, b, f;
    a = 0;
    f = 0;
    pw = p->pw;
    if (pw->pa)
        a = pw->pa->id;
    b = 0;
    if (pw->pb)
        b = pw->pb->id;
    switch (pw->table[100].fn((char *)pw + pw->table[100].delta)) {
    case 0:
        { int x = p->pw->id1134; if (a && a == x) f = 1; }
        break;
    case 1:
        break;
    case 11: {
        struct R *r = 0;
        switch (func_0013B868(p->pw)) {
        case 0x36:
            r = &p->pw->r1770;
            break;
        case 0x35:
            r = &p->pw->r1680;
            break;
        case 0x34:
            r = &p->pw->r1C90;
            break;
        }
        f = 0;
        if (b && r && b == r->id)
            f = 1;
        break;
    }
    }
    return f;

}
