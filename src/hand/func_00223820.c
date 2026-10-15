// Append the explicit entry to the receiver and register that receiver with the global collection.
// Reference algorithm: src/hand/func_0014B1A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
void func_002237F8(void *object, void *entry);
void func_0013CD10(void *list, void *object);
void func_00223820(void *object, void *entry)
{
    func_002237F8(object, entry);
    func_0013CD10(D_00475480, object);
}
