// Call the original two-input collection method with its explicit global receiver and owner.
// Reference algorithm: src/hand/func_0015E650.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0046F540[];
int func_0011B0C0(void *global, void *owner);
int func_0021DD30(void *owner)
{
    return func_0011B0C0(D_0046F540, owner);
}
