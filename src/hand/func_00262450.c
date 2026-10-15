// Find the event and either invoke its control update or store its entry index when no control is selected.
// Reference algorithm: src/hand/func_00213B00.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct E { char pad[0x10]; int id; };
struct C { char pad[8]; short h8; char pada[0xE]; };
struct A { unsigned short c; unsigned short c2; struct E *ae; struct C *ac; char padc[0x14]; int x20; char pad24[0xC]; };
struct S { char pad[0x70]; unsigned short c80; short pad82; struct A *aa; };
void func_00262D28(struct S *p, int j, int l, int y, int z);
void func_00262450(struct S *p, int k)
{
    int j, l, m;
    if (k == -1)
        return;
    for (j = 0; j < p->c80; j++) {
        struct A *a = &p->aa[j];
        for (l = 0; l < a->c; l++) {
            struct E *e = &a->ae[l];
            if (k == e->id) {
                int f = 0;
                for (m = 0; m < a->c2; m++) {
                    if (a->ac[m].h8 != -1)
                        f = 1;
                }
                if (f)
                    func_00262D28(p, j, l, 0, 0);
                else
                    a->x20 = l;
                return;
            }
        }
    }
}
