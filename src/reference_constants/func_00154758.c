// Reference algorithm: src/hand/func_00141E78.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { int id; int a, b; };
struct X { char pad[0x1250]; struct E ae[3]; };
int func_00154758(struct X *p, int id)
{
    int i;
    for (i = 0; i < 3; i++) {
        if (id == p->ae[i].id) return i;
    }
    return -1;
}
