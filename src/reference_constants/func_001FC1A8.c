// Reference algorithm: src/hand/func_001CB770.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { int pad[4]; int id; char pad2[0x58]; };
struct S { char pad[0x462C]; int c; struct E *a; };
int func_001FC1A8(struct S *p, int id)
{
    int i; struct E *entry;
    for (i = 0; i < p->c; i++)
        if ((entry = p->a + i)->id == id) return i;
    return -1;
}
