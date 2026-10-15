// Detach and destroy the owned object and release its secondary resource, clearing both pointers.
// Reference algorithm: src/hand/func_001E5370.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pf)(void *); };
struct O { char pad[0xC]; struct VTE *vt; };
struct S { char pad[0x54]; struct O *po; int n50; void *pv; };
void func_00137B00(struct O *po);
void func_00156690(void *pv);
void func_0022B678(struct S *p)
{
    if (p->po) {
        func_00137B00(p->po);
        { struct O *po = p->po; po->vt[2].pf((char *)po + po->vt[2].d); }
        p->po = 0;
    }
    if (p->pv) {
        func_00156690(p->pv);
        p->pv = 0;
    }
}
