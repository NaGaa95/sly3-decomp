// Reference algorithm: src/hand/func_001B9B70.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct O { int n; float g; int pad[2]; qword q10; qword q20; };
struct P { char pad[0x1520]; int n13D0; char pad1[0x18B0 - 0x1524]; qword q1830; };
extern qword D_00317560;
void func_00155D60(struct P *p, struct O *po);
void func_001E27B8(struct P *p, struct O *po)
{
    func_00155D60(p, po);
    switch (p->n13D0) {
    case 12:
        po->n = 1;
        po->q10 = p->q1830;
        po->q20 = D_00317560;
        break;
    case 0:
    case 1:
    case 10:
    case 11:
        po->n = 1;
        break;
    }
    po->g = 200.0f;
}
