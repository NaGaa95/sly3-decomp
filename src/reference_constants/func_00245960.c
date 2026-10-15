// Reference algorithm: src/hand/func_001FBAF8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(void *); };
struct S { int a[3]; struct VTE *vt; char pad[0x34]; int x40; char pad2[0x16]; short x52; };
void func_00245960(int x, long l) { struct S *p = (struct S *)(int)l; p->x40 = x; p->x52 = 0; p->vt[2].pfn((char *)p + p->vt[2].d); }
