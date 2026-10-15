// Copy the inherited object from the explicit source and increment its stored resource reference count.
// Reference algorithm: src/hand/func_00182E80.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { int references; };
struct S { char prefix[0xD4]; struct R *record; };
void func_0028FE20(struct S *object, void *source);
void func_002BCAA0(struct S *object, void *source)
{
    func_0028FE20(object, source);
    ++object->record->references;
}
