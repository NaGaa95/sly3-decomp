// Reference algorithm: src/hand/func_00179820.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { char pad[0xC]; struct VTE *vt; };
struct T { char pad[0x1148]; struct O *pFEC; };
struct S { char pad[0x10]; struct T *pt; };
void func_0016C9C0(struct S *p);
void func_0016D138(struct S *p) { struct O *o; func_0016C9C0(p); o = p->pt->pFEC; if (o) { struct VTE *e = &o->vt[9]; e->pfn((char *)o + e->d); } }
