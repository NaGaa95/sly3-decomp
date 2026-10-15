// Replace only original64-bit flag34 from the explicit low input bit and preserve every other original bit.
// Reference algorithm: src/hand/func_0011A1B8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0xC0]; unsigned long flags; };
void func_0023B620(struct S *p,unsigned int enabled){p->flags=(p->flags&~(1UL<<34))|((unsigned long)(enabled&1)<<34);}
