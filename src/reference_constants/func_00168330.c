// Reference algorithm: src/hand/func_0014D1D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct X { char pad[0x420]; void *owner; char pad2[12]; qword vector; };
void func_00168358(struct X *p, void *owner, qword vector);
void func_00168330(struct X *p, qword vector) { p->vector = vector; func_00168358(p, p->owner, vector); }
