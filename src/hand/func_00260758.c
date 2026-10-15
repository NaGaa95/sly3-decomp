// Find a matching event in the 20-byte descriptor array and test its active control state; handle the special event and invalid selection separately.
// Reference algorithm: src/hand/func_002121E8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct E { char pad[0x10]; int id; };
struct A { unsigned short c; short pad; struct E *ae; char pad8[0x28]; };
struct S { char pad[0x6C]; int x7C; unsigned short c80; short pad82; struct A *aa; };
int func_00267960(struct A *a);
int func_00267938(struct A *a);
int func_00260758(struct S *p, int k)
{
    int j, l;
    if (k == -1)
        return 0;
    if (p->x7C == -1)
        return 0;
    if (k == 0x37B)
        return func_00267960(p->aa) == 0;
    for (j = 0; j < p->c80; j++) {
        struct A *a = &p->aa[j];
        for (l = 0; l < a->c; l++) {
            if (k == a->ae[l].id)
                return func_00267938(a);
        }
    }
    return 0;
}
