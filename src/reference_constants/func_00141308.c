// Reference algorithm: src/hand/func_00156D98.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct K { short x; short y; int i; };
struct S { char pad[0x41C]; struct K k; };
void func_0023F400(struct S *p, void *source);
void func_00141308(struct S *p, void *source)
{
    struct K k = p->k;
    func_0023F400(p, source);
    p->k = k;
}
