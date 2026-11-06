// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Cached-record scalar getter (cf. func_00241C40) and bool accessors on the 64-bit flags word at +0x128.
typedef unsigned int U64 __attribute__((mode(DI)));
struct Record { float f0, f4, f8, fC; };
struct Owner { char prefix[0xDC]; Record *record; };
struct Actor {
    char prefix[0xD8]; Owner *owner; char gap[0x128 - 0xDC];
    struct { U64 b0:1; U64 b1:1; U64 b2:3; U64 b5:1; U64 b6:1; U64 b7:1; U64 b8:1; } flags;
};
static inline Record *PeekRecord(Actor *a) { return a->owner ? a->owner->record : 0; }
extern "C" {
float func_00241D00(Actor *a) { Record *r = PeekRecord(a); if (r) return r->f4; return 0.0f; }
bool func_00241D30(Actor *a) { return a->flags.b5; }
void func_00241D48(Actor *a, bool v) { a->flags.b5 = v; }
bool func_00241D68(Actor *a) { return a->flags.b7; }
void func_00241D80(Actor *a, bool v) { a->flags.b7 = v; }
void func_00241DA0(Actor *a, bool v) { a->flags.b1 = v; }
bool func_00241DC0(Actor *a) { return a->flags.b1; }
bool func_00241DD8(Actor *a) { return a->flags.b8; }
void func_00241DF0(Actor *a, bool v) { a->flags.b8 = v; }
}
