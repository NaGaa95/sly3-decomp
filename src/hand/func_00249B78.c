// Return the selected four-byte resource-array entry, or zero for an absent index.
// Reference algorithm: src/hand/func_001FFA40.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct E { int b; };
struct T { int a, b; struct E *ae; };
struct S { char pad[0x3F18]; struct T *pt; };
int func_00249B78(struct S *p, int n) { if (n == -1) return 0; return p->pt->ae[n].b; }
