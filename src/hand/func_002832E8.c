// Append the explicit command fields and float value with absent selector -1.
// Reference algorithm: src/hand/func_0015E650.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_00283278(void *p, int first, int second, int selector, int third, int fourth, float value);
void func_002832E8(void *p, int first, int second, int third, int fourth, float value)
{
    func_00283278(p, first, second, -1, third, fourth, value);
}
