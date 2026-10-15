// Reference algorithm: src/hand/func_001C1968.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E;
struct S { char pad[0xE8]; int xF8; int xFC; int x100; struct E *x104; struct E *x108; int *x10C; int x110; int x114; };
struct G { char pad[0x450C]; int x3D70; };
extern struct G D_00475480;
void func_001EE170(int n, struct E *a, int key);
void func_001EE220(struct S *p, int key)
{
    int i;
    for (i = 0; i < p->xFC; i++) {
        if (p->x10C[i] == key) break;
    }
    p->x10C[i] = 0;
    func_001EE170(p->x100, p->x104, i);
    func_001EE170(p->x100, p->x108, i);
    p->xF8--;
    p->x100 -= 2;
    p->x114 = ++D_00475480.x3D70;
}
