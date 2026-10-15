// Evaluate the stored resource against the explicit limit and original global context.
// Reference algorithm: src/hand/func_0014B1A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0036BD20[];
struct S { char prefix[0x1C]; void *resource; int reserved; int value; };
int func_00172268(void *global,int limit,void *resource);
void func_00240C78(struct S *object,int limit)
{
    object->value=func_00172268(D_0036BD20,limit,object->resource);
}
