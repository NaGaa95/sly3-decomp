// Reset the inherited object and clear its selection using the embedded reference.
// Reference algorithm: src/hand/func_0014B1A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_002621F0(void *object);
void func_00262B60(void *object, int selection, void *reference);
void func_0021E520(void *object)
{
    func_002621F0(object);
    func_00262B60(object, -1, (char *)object + 0x144);
}
