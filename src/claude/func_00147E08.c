// SLY3_CFLAGS: -Os -G0
struct REQ { int cb; int align; };
void *func_001D2470(struct REQ *r);
struct VirtualEntry { short delta, reserved; void (*call)(void *); };
struct E { int a; int b; void *c; };
struct O { char pad[0xC]; struct VirtualEntry *table; char pad2[0xA4 - 0x10]; int xA4; char pad3[0xB0 - 0xA8];
           int stride; int n; char *base; int m; struct E *e; };
struct O *func_00150690(int k, void *a, int b, int c);
extern char D_0036B118[];
void func_00147FD0(struct O *o, void *p);
void func_00147E08(void *kind, int stride, int n, char *base, int m, int *arr1, int *arr2, struct O **out)
{
    struct O *first = 0;
    int any = 0;
    int i;
    struct O *o;
    struct REQ r;
    {
        int j;
        for (j = 0; j < n; j++) {
            struct O *q = *(struct O **)(base + j * stride + 4);
            if (q) {
                if (!first)
                    first = q;
                if (q->xA4)
                    any = 1;
            }
        }
    }
    if (!first) {
        *out = 0;
        return;
    }
    o = func_00150690(0x83, kind, -1, -1);
    o->table[9].call((char *)o + o->table[9].delta);
    o->stride = stride;
    o->n = n;
    o->base = base;
    o->m = m;
    r.cb = m * 12;
    r.align = 16;
    o->e = func_001D2470(&r);
    for (i = 0; i < m; i++) {
        struct E *e = &o->e[i];
        e->a = arr1[i];
        e->b = arr2[i];
        r.cb = e->b * 8;
        r.align = 16;
        e->c = func_001D2470(&r);
    }
    o->xA4 = any;
    if (!any)
        func_00147FD0(o, D_0036B118);
    *out = o;
}
