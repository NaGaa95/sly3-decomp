// Reference algorithm: src/hand/func_0019C870.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct O { char pad[0x560]; int x520; };
struct S { struct O *p; int pad[6]; int x1c; char pad2[0x70-0x20]; int c0; int c4; };
int func_001BD718(struct S *s, int *pn) {
    int v;
    switch (s->x1c) {
    case 0xC: case 0xD: case 0xE: v = s->p->x520; break;
    case 0x12: v = s->c4; break;
    default: v = s->c0; break;
    }
    *pn = 0;
    return v;
}
