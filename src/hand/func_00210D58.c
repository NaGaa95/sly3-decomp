// Submit the owner state with both explicit option bytes cleared.
// Reference algorithm: src/hand/func_001F0198.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_00210D78(void *owner, int first, int second);
void func_00210D58(void *owner)
{
    func_00210D78(owner, 0, 0);
}
