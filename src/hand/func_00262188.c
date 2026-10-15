// The original event helper reads incoming A1; pass the key explicitly.
// Clear the event criterion using the explicit incoming key, invoke the virtual state notification, update a prior selection if needed, and store the key.
// Reference algorithm: src/hand/func_00213830.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct VE { short d; short pad; void (*pf)(void *, int); };
struct S { char pad[0xC]; struct VE *vt; char pad2[0x5C]; int x7c; char pad3[4]; void *x84; char pad4[0x24]; int xac; };
void func_00266F20(void *p, int k);
void func_00263080(struct S *p, int a);
void func_00262188(struct S *p, int a)
{
    func_00266F20(p->x84, a);
    p->vt[23].pf((char *)p + p->vt[23].d, 1);
    if (p->xac)
        func_00263080(p, 0);
    p->x7c = a;
}
