// Reference algorithm: src/hand/func_0017F138.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(void *); };
struct S { char pad[0xC]; struct VTE *vt; };
void func_001C7DC8(struct S *p);
void func_00212738(struct S *p) { struct VTE *e; func_001C7DC8(p); e = &p->vt[0x9]; e->pfn((char *)p + e->d); }
