// SLY3_CFLAGS: -Os -G0
// Store the value at +0x2F0 and set +0x1018 to whether it is zero.
struct State { char prefix[0x2F0]; int value; char gap[0x1018 - 0x2F4]; int none; };
void func_00250B58(struct State *s, int v) { s->value = v; if (!v) s->none = 1; else s->none = 0; }
