// SLY3_CFLAGS: -O2 -G0 -fno-cse-skip-blocks -fno-schedule-insns2
// Clear the "pending" bit (4) of an object's tagged flag word unless the parent's shared flag word already has it set.
// The tagged word is either a plain value (low bit set) or a pointer to the shared word; while the shared word has
// the lock bit (0x20) the pending bit is left alone. Same routine as Sly 2 func_001A5E80 (offsets differ in Sly 3,
// which also keeps the lock-bit test).
struct Parent { char pad[0x3C]; int flags; };
struct Owner { char pad[0x10]; struct Parent *parent; char pad14[0x28]; int flags; };
static inline void ClearFlags(struct Owner *owner, int bits)
{
    int tagged = owner->flags;
    int clear = bits;
    if (bits & 4) {
        unsigned int current = ((tagged ^ 1) & 1) ? *(unsigned int *)tagged : tagged;
        if (current & 0x20)
            clear = bits & ~4;
    }
    if ((tagged ^ 1) & 1)
        *(int *)tagged &= ~clear;
    else
        owner->flags = tagged & ~clear;
}
void func_001C81B8(struct Owner *owner)
{
    if (!owner->parent || !(*(unsigned int *)owner->parent->flags & 4)) {
        int pending = 4;
        ClearFlags(owner, pending);
    }
}
