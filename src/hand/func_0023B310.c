// Release a reference-counted pooled resource and recursively clear the resources of matching child objects.
// Reference algorithm: src/hand/func_001F2468.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { int pad[2]; int c; };
struct L { char pad[0x24]; struct L *next; char pad2[0x54 - 0x28]; struct L *first; char pad3[0x60 - 0x58]; struct L *end; char pad4[0x10C - 0x64]; struct R *pr; };
struct Pool;
extern struct Pool D_00479A48;
void func_0011E1F0(struct Pool *, struct R *);
int func_0013B500(struct L *, int);
void func_0023B310(struct L *p)
{
    struct L *q;
    struct R *pr = p->pr;
    if (pr) {
        if (--pr->c == 0) func_0011E1F0(&D_00479A48, pr);
        p->pr = 0;
    }
    for (q = p->first; q != p->end; q = q->next) {
        if (func_0013B500(q, 0x2F)) func_0023B310(q);
    }
}
