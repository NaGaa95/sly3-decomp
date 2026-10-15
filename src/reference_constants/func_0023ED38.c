// Reference algorithm: src/hand/func_001F5860.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
extern qword D_00317560;
struct T { char pad[0x80]; qword v; };
struct S { char pad[0xD8]; struct T *pt; };
qword func_0023ED38(struct S *p) { if (!p->pt) return D_00317560; return p->pt->v; }
