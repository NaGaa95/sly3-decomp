// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Bitfield accessors on the 64-bit flags word at +0x120.
typedef unsigned int U64 __attribute__((mode(DI)));
typedef int S64 __attribute__((mode(DI)));
struct FlagObject {
    char prefix[0x120];
    struct { U64 low:48; S64 level:4; U64 mid:9; U64 bit61:1; U64 top:2; } flags;
};
extern "C" {
void func_00241590(FlagObject *p, int v) { p->flags.level = v; }
int func_002415C8(FlagObject *p) { return p->flags.level; }
bool func_002415E0(FlagObject *p) { return p->flags.bit61; }
void func_002415F0(FlagObject *p, bool v) { p->flags.bit61 = v; }
}
