// SLY3_CFLAGS: -Os -G0
// Return the word at +0x10D0.
struct State { char prefix[0x10D0]; int value; };
int func_00250D58(struct State *s) { return s->value; }
