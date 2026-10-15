// Set the original state six and associate the explicit object with the global resource.
// Reference algorithm: src/hand/func_001E7930.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern void *D_00468D24;
void func_002159D8(void *object,int state);
void func_0021A570(void *resource,void *object);
void func_00218B68(void *object)
{
    func_002159D8(object,6);
    func_0021A570(D_00468D24,object);
}
