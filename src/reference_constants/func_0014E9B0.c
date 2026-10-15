// Reference algorithm: src/hand/func_0013CEF8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct G { char pad[0x4E50]; int c; };
extern struct G D_00475480;
struct S { char pad[0x190]; int id; };
void func_001A1E58(struct S *);
void func_0014E9B0(struct S *p) { func_001A1E58(p); p->id = D_00475480.c++; }
