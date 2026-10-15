// Reference algorithm: src/hand/func_001FE0E8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { short s0; short k; union { int n; float g; } u; };
struct P { char pad[0x23C]; void *ap[3]; void *p238; };
void func_00241928(void *, float);
void func_00239CE8(void *, int);
void func_002480C8(struct P *p, struct E *pe)
{
    int k = pe->k;
    if (k != -1 && p->ap[k]) {
        if (k == 3) func_00241928(p->p238, pe->u.g);
        else if (pe->u.n != -1) func_00239CE8(p->ap[k], pe->u.n);
    }
}
