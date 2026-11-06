// SLY3_CFLAGS: -Os -G0
// Increment the counter at +0x10 (vtable slot split out of func_00240850's row).
struct Counter { char prefix[0x10]; int count; };
void func_00240970(struct Counter *p) { p->count++; }
