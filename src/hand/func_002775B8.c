// Select the mode notification argument based on the current state and invoke the verified virtual method.
// Reference algorithm: src/hand/func_002245B8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pf)(void *, int); };
struct S { int a[3]; struct VTE *vt; char pad[0x12C]; int k; };
void func_002775B8(struct S *p)
{
    if (p->k == 10) p->vt[80].pf((char *)p + p->vt[80].d, 5);
    else p->vt[80].pf((char *)p + p->vt[80].d, 3);
}
