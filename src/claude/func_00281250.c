// SLY3_CFLAGS: -Os -G0
// Port of Sly 2 func_00229798.
struct VTE { short d; short pad; void (*pf)(void *, void *); };
struct O { int a[3]; struct VTE *vt; };
struct N { struct O *po; int a; struct N *next; };
struct S { char pad[0x110]; struct N *first; };
void func_00281250(struct S *p)
{
    struct N *n;
    for (n = p->first; n; n = n->next) {
        struct O *po = n->po;
        po->vt[75].pf((char *)po + po->vt[75].d, n);
    }
}

/* 0x2812A8: empty function swallowed by this csv entry. */
void func_002812A8(void)
{
}
