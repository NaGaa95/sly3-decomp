// Run the inherited reset and explicitly enable the object.
// Reference algorithm: src/hand/func_00174920.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_001F3BF8(void *p);
void func_001F4670(void *p, int enabled);
void func_00209FA0(void *p)
{
    func_001F3BF8(p);
    func_001F4670(p, 1);
}
