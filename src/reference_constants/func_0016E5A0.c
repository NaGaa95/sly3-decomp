// Reference algorithm: src/hand/func_00155560.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { int pad[4]; int n10; int pad2[7]; int n30; };
void func_00238970(struct S *p);
void func_00252E40(int n, int k);
void func_0016E5A0(struct S *p)
{
    func_00238970(p);
    func_00252E40(p->n10, 0xC);
    p->n30 = -1;
}
