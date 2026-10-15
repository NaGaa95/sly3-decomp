// Initialize the owner, then traverse its child range and invoke each child callback.
// Reference algorithm: src/hand/func_0022FBE0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pf)(void *); };
struct O { int a[3]; struct VTE *vt; char pad[0x14]; struct O *next; };
struct S { char pad[0x54]; struct O *first; int a[2]; struct O *end; };
void func_0028E768(struct S *p);
void func_0028E8A8(struct S *p)
{
    struct O *o;
    func_0028E768(p);
    for (o = p->first; o != p->end; o = o->next)
        o->vt[20].pf((char *)o + o->vt[20].d);
}
