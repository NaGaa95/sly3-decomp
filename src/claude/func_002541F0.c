// SLY3_CFLAGS: -Os -G0
// Store the word at +0x3B0.
struct State { char prefix[0x3B0]; int value; };
void func_002541F0(struct State *s, int v) { s->value = v; }
