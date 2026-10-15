// Reference algorithm: src/hand/func_001C2170.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct E { qword q; int pad[4]; };
struct S { char pad[0x40]; int c; char pad2[0xC]; struct E a[6]; char pad3[4]; int n124; int n128; int pad4; qword q130; qword q140; };
void func_001C7DC8(struct S *p);
qword func_001EE7F8(struct E *pe);
int func_001ED678(qword q, int n);
void func_001EEA28(struct S *p)
{
    func_001C7DC8(p);
    p->q130 = func_001EE7F8(&p->a[0]);
    p->n124 = func_001ED678(p->q130, 0);
    p->q140 = func_001EE7F8(/*B*/&p->a[p->c] - 1/*E*/);
    p->n128 = func_001ED678(p->q140, 0);
}
