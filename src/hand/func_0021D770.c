// Initialize the returned list's link offset to 16 bytes.
// Reference algorithm: src/hand/func_00120CC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_0011AF38(void *ret, int offset);
void *func_0021D770(void *ret)
{
    func_0011AF38(ret, 0x10);
    return ret;
}
