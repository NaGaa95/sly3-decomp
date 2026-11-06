// SLY3_CFLAGS: -Os -G0
// True when the target lacks flag 0x10000 and has a positive count at +0x80.
typedef unsigned int U64 __attribute__((mode(DI)));
struct Target { char prefix[0x18]; U64 flags; char gap[0x80 - 0x20]; int count; };
int func_0024C260(void *self, struct Target *t) { return !(t->flags & 0x10000) && t->count > 0; }
