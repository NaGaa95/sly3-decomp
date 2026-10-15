// Update the selected indexed state using the explicit incoming enabled flag, then reset the associated global collection.
// Reference algorithm: src/hand/func_0014C2B0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_0021F510(int index, int enabled);
void func_001C0130(void *p);
extern char D_00475480[];
void func_0021F5D0(int index, int enabled)
{
    func_0021F510(index, enabled);
    func_001C0130(D_00475480);
}
