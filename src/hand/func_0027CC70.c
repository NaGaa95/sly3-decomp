// Copy from the explicit source and repair a self-reference that still points at that source.
// Reference algorithm: src/hand/func_001A35B0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x1E0]; void *reference; };
void func_0023F400(struct S *object,void *source);
void func_0027CC70(struct S *object,void *source)
{
    func_0023F400(object,source);
    if(object->reference==source)object->reference=object;
}
