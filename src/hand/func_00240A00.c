// Call the original two-input collection method with its explicit global receiver and owner.
// Reference algorithm: src/hand/func_0015E650.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00479DB4[];
void func_0011E1F0(void *global, void *owner);
void func_00240A00(void *owner)
{
    func_0011E1F0(D_00479DB4, owner);
}
