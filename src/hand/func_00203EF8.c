// Run the inherited cleanup, release both embedded owned references, and finish the object cleanup.
// Reference algorithm: src/hand/func_00132100.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_001F3C80(void *object);
void func_00137628(void *record);
void func_00205168(void *object);
void func_00203EF8(void *object)
{
    func_001F3C80(object);
    func_00137628((char *)object + 0x420);
    func_00137628((char *)object + 0x424);
    func_00205168(object);
}
