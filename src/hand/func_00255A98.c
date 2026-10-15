// Read the selected object value only while the query predicate is active.
// Reference algorithm: src/hand/func_0020A010.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct O { char pad[0x58]; int n; };
int func_002533C0(void *p, int n);
struct O *func_002387A8(void *p, int oid);
int func_00255A98(void *p) { if (func_002533C0(p, 0x2A)) return func_002387A8((char *)p + 0x29C, 0xDA)->n; return 0; }
