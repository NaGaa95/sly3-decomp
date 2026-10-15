// Evaluate the explicit16-bit resource property and multiply its float result by the receiver scale.
// Reference algorithm: src/hand/func_001A5BF0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x8]; void * owner; char unknown_C[0x7C]; float scale; };
float func_00265DE0(void *owner,unsigned short id);
float func_00264E78(struct S *object,unsigned short id)
{
    return func_00265DE0(object->owner,id)*object->scale;
}
