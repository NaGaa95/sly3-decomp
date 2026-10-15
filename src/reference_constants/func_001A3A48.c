// Reference algorithm: src/hand/func_001753D8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x10]; void *p10; char pad2[0x20]; int n34; };
void func_00238970(struct S *p);
void func_00252E40(void *p, int n);
void func_001A3A48(struct S *p) { func_00238970(p); func_00252E40(p->p10, 0x31); p->n34 = -1; }
