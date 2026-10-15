// Initialize the inherited object and embedded state, then reset its selection to -1.
// Reference algorithm: src/hand/func_001BC050.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_001FCAC8(void *p);
void func_00278D68(void *p);
void func_00278E58(void *p, int selector);
void func_00278D30(void *p)
{
    func_001FCAC8(p);
    func_00278D68(p);
    func_00278E58(p, -1);
}
