// Reset the inherited object, clear its selection, and release the embedded owned record.
// Reference algorithm: src/hand/func_00146EE0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_001FCB20(void *object);
void func_00232A38(void *object, int selection);
void func_00137628(void *record);
void func_00232440(void *object)
{
    func_001FCB20(object);
    func_00232A38(object, -1);
    func_00137628((char *)object + 0x138);
}
