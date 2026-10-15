// Run the original conditional destructor release hook when flag bit zero is set.
// Reference algorithm: src/hand/func_0014D1D0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_001D2818(void *object);
void func_002BF740(void *object, int flags)
{
    if (flags & 1) func_001D2818(object);
}
