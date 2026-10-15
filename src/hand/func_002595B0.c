// Call the original two-input collection method with its explicit global receiver and owner.
// Reference algorithm: src/hand/func_0015E650.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0047A2E0[];
void func_0011E1F0(void *global, void *owner);
void func_002595B0(void *owner)
{
    func_0011E1F0(D_0047A2E0, owner);
}
