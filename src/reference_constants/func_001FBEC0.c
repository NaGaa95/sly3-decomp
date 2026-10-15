// Reference algorithm: src/hand/func_001CB2E0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct T { int a; int *ap; };
struct S { char pad[0xD0]; struct T *pt; int x; void *pe8; };
int func_001FB5D8(struct S *p, void *q);
int func_001FBEC0(struct S *p)
{
    /*B*/int i; if (!p->pe8) return 0; i = func_001FB5D8(p, p->pe8); return p->pt->ap[i];/*E*/
}
