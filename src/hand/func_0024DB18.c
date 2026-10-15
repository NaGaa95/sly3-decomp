// Update the owner and its embedded record at 0x29C through two explicit receiver calls.
// Reference algorithm: src/hand/func_001C3DC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_001F3C80(void *owner);
void func_00238568(void *record);
void func_0024DB18(void *owner)
{
    func_001F3C80(owner);
    func_00238568((char *)owner + 0x29C);
}
