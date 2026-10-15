// Return whether the explicit object is absent from the original global linked list.
// Reference algorithm: src/hand/func_001AE4F8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00479A08[];
int func_0011B0C0(void *list,void *object);
int func_00239CC0(void *object)
{
    return !func_0011B0C0(D_00479A08,object);
}
