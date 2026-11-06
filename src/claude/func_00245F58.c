// SLY3_CFLAGS: -Os -G0
// Increment the 16-bit counter at +0x58.
struct Counter { char prefix[0x58]; unsigned short count; };
void func_00245F58(struct Counter *p) { p->count++; }
