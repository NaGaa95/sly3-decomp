// Submit the explicit rectangle, selector two, and embedded graphics packet.
// Reference algorithm: src/hand/func_0015E650.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_0025FBF8(void *rectangle, int selector, void *packet);
void func_002643D0(void *owner, void *rectangle)
{
    func_0025FBF8(rectangle, 2, (char *)owner + 0x100);
}
