// Reference algorithm: src/hand/func_0018A2E0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -O2 -G0
typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x19A4]; int n; char p1[8]; qword aq[3]; char p2[0xCC]; float g; };
void func_0023E290(struct S *p);
void func_0023E940(struct S *p, qword q, float g);
void func_001ABA10(struct S *p)
{
    int i;
    func_0023E290(p);
    for (i = 0; i < p->n; i++)
        func_0023E940(p, p->aq[i], p->g);
}
