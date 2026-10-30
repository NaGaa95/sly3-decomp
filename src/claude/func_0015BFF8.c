// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta, reserved; void *(*call)(void *); };
struct E { int id; int a; int b; };
struct S { char pad[0x14]; int f14; char pad18[0x70 - 0x18]; void *f70; int f74; char f78[0xB8 - 0x78]; int fB8; char fBC[0xDC - 0xBC]; int count; struct E entries[1]; };
extern char D_00475480[];
extern char D_0036C700[];
void func_0025D3F8(void *g, int a, void *b, void *x, int on);
void *func_0017E1B8(void *g, int kind, int id, void *x);
int func_0013B500(void *object, int kind);
void func_002261A0(void *o, int n);
void func_002261F0(void *o, int n);
void func_00225EE8(void *a, int b);
void func_00185908(void *g, int a, void *b, void *x);

void func_0015BFF8(struct S *s, int on)
{
    struct VirtualEntry *table = *(struct VirtualEntry **)((char *)s + 0xEC);
    void *x = table[1].call((char *)s + table[1].delta);
    int i;
    func_0025D3F8(D_00475480, s->f74, s->f78, x, on != 0);
    for (i = 0; i < s->count; i++) {
        struct E *e = &s->entries[i];
        void *o = func_0017E1B8(D_00475480, 4, e->id, x);
        if (!o)
            continue;
        if (!func_0013B500(o, 0x87))
            continue;
        if (on) {
            if (e->a != -1)
                func_002261A0(o, e->a);
        } else if (e->b == e->a) {
            if (e->b != -1)
                func_002261F0(o, e->b);
        } else {
            if (e->b != -1)
                func_002261A0(o, e->b);
        }
    }
    if (on) {
        if (s->f70)
            func_00225EE8(s->f70, s->f14);
        func_00185908(D_0036C700, s->fB8, s->fBC, x);
    }
}
