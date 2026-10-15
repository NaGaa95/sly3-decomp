// Append the explicit command fields and float value with both absent selectors set to -1.
// Reference algorithm: src/hand/func_001AE4F8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_00283278(void *object, int first, int second, int selector, int third, int fourth, float value);
void func_002832C0(void *object, int first, int third, int fourth, float value)
{
    func_00283278(object, first, -1, -1, third, fourth, value);
}
