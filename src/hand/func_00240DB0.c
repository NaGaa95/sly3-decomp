// Call the original two-input collection method with its explicit global receiver and owner.
// Reference algorithm: src/hand/func_0015E650.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
void func_0025DEF8(void *global, void *owner);
void func_00240DB0(void *owner)
{
    func_0025DEF8(D_00475480, owner);
}
