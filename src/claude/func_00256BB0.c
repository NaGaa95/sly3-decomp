// SLY3_CFLAGS: -Os -G0
// Store an angle given in degrees as radians at +0x58.
struct State { char prefix[0x58]; float angle; };
void func_00256BB0(struct State *s, float degrees) { s->angle = degrees * 0.0174532942f; }
