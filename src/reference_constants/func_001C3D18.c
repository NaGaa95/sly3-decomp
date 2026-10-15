// Reference algorithm: src/hand/func_001A2100.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern float D_003457E4, D_003457E8;
struct Q { char pad[0x94]; float x94; float x98; };
struct S { int x0; int x4; };
void func_001C3D18(struct S *p, struct Q *q)
{
    switch (p->x4) {
    case 4: case 13:
        q->x94 = D_003457E4;
        q->x98 = 0;
        break;
    case 0: case 6: case 7: case 8:
        break;
    default:
        q->x94 = D_003457E4;
        q->x98 = D_003457E8;
        break;
    }
}
