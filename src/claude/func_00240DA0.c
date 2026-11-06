// SLY3_CFLAGS: -Os -G0
// Return whether the second argument's field at +0x50 is set (vtable slot after func_00240CB0).
struct Target { char prefix[0x50]; int value; };
int func_00240DA0(void *self, struct Target *p) { return p->value != 0; }
