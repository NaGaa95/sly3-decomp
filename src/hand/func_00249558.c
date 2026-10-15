// Update the owner and its embedded record at 0xF8 through two explicit receiver calls.
// Reference algorithm: src/hand/func_001C3DC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_001C81B8(void *owner);
void func_0015CE68(void *record);
void func_00249558(void *owner)
{
    func_001C81B8(owner);
    func_0015CE68((char *)owner + 0xF8);
}
