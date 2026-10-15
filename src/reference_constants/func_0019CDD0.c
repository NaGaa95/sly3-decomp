// Reference algorithm: src/hand/func_00180500.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x1F0]; int x1c0; char p0[0x5C]; char x220[0x150]; float x338; char p1[0xC]; float x340; char p2[0xC]; float x350; char p3[0x10]; float x364; char p4[8]; float x370; float x374; };
void func_0019B420(struct S *p);
void func_0019DDC8(struct S *p, float g);
void func_0019DDF8(struct S *p, float g);
void func_0019B940(struct S *p, int n, void *pv);
void func_0019CDD0(struct S *p)
{
    func_0019B420(p);
    p->x340 = 1.0f;
    p->x350 = 1.0f;
    p->x364 = 1.0f;
    p->x338 = 250.0f;
    p->x370 = -3.40282346638528859812e+38f;
    p->x374 = 3.40282346638528859812e+38f;
    func_0019DDC8(p, 1.0f);
    func_0019DDF8(p, 1.0f);
    func_0019B940(p, 6, p->x220);
    p->x1c0 = -1;
}
