// Reference algorithm: src/hand/func_001C7E68.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(void *, int); };
struct O { int a[3]; struct VTE *vt; char unknown[0x1440 - 0x10]; int value; };
void func_002502E8(struct O *p);
void func_00156A70(struct O *p)
{
    func_002502E8(p);
    { struct VTE *e = &p->vt[84]; e->pfn((char *)p + e->d, p->value); }
}
