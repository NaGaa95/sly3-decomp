// Find the event and invoke its update with the explicit group index, entry index, and requested control value.
// Reference algorithm: src/hand/func_00213BD8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct E { char pad[0x10]; int id; };
struct A { unsigned short c; short pad; struct E *ae; char pad8[0x28]; };
struct S { char pad[0x70]; unsigned short c80; short pad82; struct A *aa; };
void func_00262E98(struct S *p, int j, int l, int x, int y, int z);
void func_00262540(struct S *p, int k, int x)
{
    int j, l;
    for (j = 0; j < p->c80; j++) {
        struct A *a = &p->aa[j];
        for (l = 0; l < a->c; l++) {
            struct E *e = &a->ae[l];
            if (k == e->id) {
                func_00262E98(p, j, l, x, 0, 0);
                return;
            }
        }
    }
}
