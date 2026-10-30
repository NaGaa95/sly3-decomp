// SLY3_CFLAGS: -Os -G0
struct O { char pad[0x30]; char list[0xE0 - 0x30]; int xE0; };
struct W { char pad[0x50]; char list[0x10]; };
struct S { char pad[0x40]; struct W *pw; char pad2[0x58 - 0x44]; struct O *po; };
struct O *func_00172A90(struct S *p, int id);
void func_00172BA8(struct S *p, int x);
void func_0016F2B0(struct W *pw, int x);
void func_00258A10(void *pl, void *pv);
void func_00172C30(struct S *p, int id)
{
    struct O *o;
    if (id == -1)
        return;
    o = func_00172A90(p, id);
    if (!o || o == p->po)
        return;
    if (p->po)
        func_00172BA8(p, p->po->xE0);
    if (o && p->pw) {
        func_0016F2B0(p->pw, o->xE0);
        func_00258A10(o->list, p->pw->list);
    }
    p->po = o;
}
