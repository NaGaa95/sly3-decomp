// Reference algorithm: src/hand/func_001AF390.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct F { int pad[5]; void (*pfn)(struct F *); int pad2[2]; };
struct E { int n; struct F *af; int x8; int xC; int x10; int x14; int x18; };
struct S { int pad[8]; struct E a[1]; };
struct S1 { char pad[0x200]; int x1EC; };
void func_001D2ED0(struct S *s, int n);
void *func_00292034(void *p, int c, unsigned int n);
void func_001D3818(struct S *s, int n, struct F *af)
{
    int x18, x8;
    int k;
    struct E *e;
    int i;
    func_001D2ED0(s, 3);
    k = s->a[0].x18;
    if (k > 0) {
        e = &s->a[k];
        x8 = e->x8;
        x18 = e->x18;
    }
    ((struct S1 *)s)->x1EC = k + 1;
    e = &s->a[k + 1];
    func_00292034(e, 0, sizeof(*e));
    e->af = af;
    e->x8 = x8;
    e->xC = 1;
    e->x18 = x18;
    e->n = n;
    for (i = 0; i < e->n; i++) {
        struct F *f = &e->af[i];
        if (f->pfn)
            f->pfn(f);
    }
}
