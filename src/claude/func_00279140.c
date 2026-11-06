// SLY3_CFLAGS: -Os -G0
// Two functions that config/functions.csv currently lumps into func_00279140.
struct E { int a; int b; };
struct S { char pad[0x54]; unsigned int c; struct E e[32]; };
void func_00278E58(struct S *p, int k);
void func_00279140(struct S *p)
{
    func_00278E58(p, 1);
}
void func_00279160(struct S *p, int a)
{
    unsigned int c = p->c;
    if (c < 32) {
        struct E *e = &p->e[c];
        p->c = c + 1;
        e->a = a;
        e->b = 0;
    }
}
