// Reset the receiver only when the explicit source has an available resource.
// Reference algorithm: src/hand/func_001A2358.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x50]; void *resource; };
void func_00287AF8(void *object,struct S *source);
int func_00287B10(void *object,struct S *source)
{
    if(!source->resource)return 0;
    func_00287AF8(object,source);
    return 1;
}
