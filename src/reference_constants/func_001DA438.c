// Reference algorithm: src/hand/func_0017CAC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x10]; void *p10; char pad2[0x1C]; int n30; int pad3; float g38; };
void func_00238970(struct S *p);
void func_00252E40(void *p, int n);
void func_001DA438(struct S *p) { func_00238970(p); p->n30 = -1; p->g38 = 1.0f; func_00252E40(p->p10, 0x2F); }
