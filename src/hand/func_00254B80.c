// Return the ready flag or the original fallback global selection predicate.
// Reference algorithm: src/hand/func_00207598.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
struct S { char prefix[0x1134]; int ready; };
int func_001A95D0(void *global,int selection);
int func_00254B80(struct S *object)
{
    if(object->ready)return 1;
    return func_001A95D0(D_00475480,-1);
}
