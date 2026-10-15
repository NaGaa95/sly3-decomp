// Reference algorithm: src/hand/func_00217BA0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { char pad[0x10]; int id; };
struct S { unsigned short c; short pad; struct E *a; char pad8[0x20]; int x28; };
void func_00266FA0(struct S *p, int i);
void func_00266F20(struct S *p, int k)
{
    int i;
    if (p->x28) {
        i = 0;
        if (k != 0x37B) {
            for (i = 0; i < p->c; i++)
                if (k == p->a[i].id) break;
            if (i >= p->c) i = 0;
        }
        func_00266FA0(p, i);
    }
}
