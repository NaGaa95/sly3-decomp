// Disable the object only when its original active-object predicate succeeds.
// Reference algorithm: src/hand/func_0014B1A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
int func_0021A710(void *object);
void func_00219A18(void *object, int enabled);
void func_0021A418(void *object)
{
    if (func_0021A710(object)) func_00219A18(object, 0);
}
