// SLY3_CFLAGS: -Os -G0
// Set the value at +0x214; a change to a non-zero value clears +0x218.
struct State { char prefix[0x214]; int value; int aux; };
void func_0024E180(struct State *s, int v) { if (s->value != v) { s->value = v; if (v) s->aux = 0; } }
