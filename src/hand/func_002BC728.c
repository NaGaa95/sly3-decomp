// Construct a returned reference from the owner's embedded selection record at 0x120; actual callee inputs are receiver and record pointer.
// Reference algorithm: src/hand/func_00120CC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_0015C5D8(void *ret, void *source);
void *func_002BC728(void *ret, void *owner)
{
    func_0015C5D8(ret, (char *)owner + 0x120);
    return ret;
}
