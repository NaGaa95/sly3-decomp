// Reference algorithm: src/hand/func_00171C18.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct K { int k; };
struct R { struct K *pk; int n; float g; };
struct U { char pad[0x38]; float g38; };
struct T { char pad[0x10F0]; int nF80; };
struct S { char pad[0x10]; struct T *pt; int pad1; struct U *p18; char pad2[0x18]; int n34; struct K *p38; };
void *func_00292034(void *p, int c, int n);
void func_001982C8(struct S *p, struct R *r) {
    switch (p->pt->nF80) {
    case -1:
        r->pk = p->p38;
        r->n = p->n34;
        if (r->pk && r->pk->k == 6) r->g = p->p18->g38;
        break;
    case 0: case 1:
        func_00292034(r, 0, sizeof(*r));
        break;
    }
}
