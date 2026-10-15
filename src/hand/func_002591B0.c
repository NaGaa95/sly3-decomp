// Reset the present stored owner using the explicit associated arguments and original zero/one float controls.
// Reference algorithm: src/hand/func_001A30D0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x40]; void * owner; };
void func_00136908(void *owner,void *first,void *second,void *output,float value,float scale);
void func_002591B0(struct S *object,void *first,void *second,void *output)
{
    if(object->owner)func_00136908(object->owner,first,second,output,0.0f,1.0f);
}
