// Reference algorithm: src/hand/func_001904E0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct O { int a; int b; };
struct S { char pad[0x1A04]; struct O *p; char pad2[0x1A30-0x1A08]; qword a; qword b; };
void func_00244828(int, qword);
void func_00244890(int, qword);
void func_001B18E0(struct S *s) { func_00244828(s->p->b, s->a); func_00244890(s->p->b, s->b); }
