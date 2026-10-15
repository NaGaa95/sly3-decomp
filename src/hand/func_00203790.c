// Update the owner and its embedded record at 0x1A8 through two explicit receiver calls.
// Reference algorithm: src/hand/func_001C3DC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_0022DCC8(void *owner);
void func_0015CE68(void *record);
void func_00203790(void *owner)
{
    func_0022DCC8(owner);
    func_0015CE68((char *)owner + 0x1A8);
}
