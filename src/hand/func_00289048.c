// Submit the stored default record with kind 0x1A8, mode 2, and absent selection.
// Reference algorithm: src/hand/func_00119C08.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_00289070(void *object, void *record, int kind, int mode, int selection);
void func_00289048(void *object)
{
    func_00289070(object, 0, 0x1A8, 2, -1);
}
