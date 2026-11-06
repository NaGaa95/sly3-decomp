// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Return whether bit 19 of the target's 64-bit flags word at +0x18 is clear (vtable slot after func_002812B0).
typedef unsigned int U64 __attribute__((mode(DI)));
struct Target { char prefix[0x18]; struct { U64 low:19; U64 bit19:1; } flags; };
extern "C" bool func_00281850(void *self, Target *t) { return !t->flags.bit19; }
