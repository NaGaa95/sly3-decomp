// Reference algorithm: src/hand/func_001F4440.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
extern qword D_00317560;
struct T { char pad[0x70]; qword v; char pad2[0x14]; int n; };
struct S { char pad[0x48]; struct T *pt; };
qword func_0028BCD0(struct T *, int, qword);
qword func_0023D480(struct S *p) { struct T *pt = p->pt; if (!pt || pt->n != 1) return D_00317560; return func_0028BCD0(pt, 0, pt->v); }
