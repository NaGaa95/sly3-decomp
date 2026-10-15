// Reference algorithm: src/hand/func_00184268.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0xE0]; int f0; char p1[12]; int fc; char p2[0xA0]; int x184; int p3; int x18c; int p4; int x194; int p5; int x19c; };
void func_001A1D70(struct S *p);
void func_001A21E0(struct S *p)
{
    func_001A1D70(p);
p->x184 = -1;
p->x18c = -1;
p->x194 = -1;
p->x19c = -1;
p->f0 = -1;
p->fc = 4;
}
