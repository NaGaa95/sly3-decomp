// Reference algorithm: src/hand/func_00229738.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct N { int a[2]; struct N *next; };
struct S { char pad[0x110]; struct N *first; };
void func_0023E228(struct S *p, struct N *n);
void func_002811F0(struct S *p, struct N *n)
{
    struct N **pp;
    for (pp = &p->first; *pp; pp = &(*pp)->next) {
        if (*pp == n) { *pp = n->next; n->next = 0; break; }
    }
    func_0023E228(p, n);
}
