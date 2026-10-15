// Apply the original update with option zero and complete the receiver cleanup.
// Reference algorithm: src/hand/func_00174920.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_0021B4F8(void *object,int option);
void func_00260E30(void *object);
void func_0021BC28(void *object)
{
    func_0021B4F8(object,0);
    func_00260E30(object);
}
