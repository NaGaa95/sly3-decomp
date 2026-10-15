// Reference algorithm: src/hand/func_00184380.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct T { char pad[0xE4]; int n; };
struct S { char pad[0x190]; int x; char pad2[0x18]; int n; };
int func_001C8F20(struct T *q, int x);
int func_001A22F8(struct S *p, struct T *q)
{
    if (q->n != p->n) return 1;
    return func_001C8F20(q, p->x);
}
