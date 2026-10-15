// Reference algorithm: src/hand/func_0017DD38.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Q2 { qword a, b; };
struct S { char pad[0x40]; struct Q2 q; char pad2[0x20]; float gA0; };
void func_001D7D10(struct S *p);
void func_001D7FD0(struct S *p, struct Q2 *pq) { p->q = *pq; p->gA0 = -3.40282346638528859812e+38f; func_001D7D10(p); }
