// Release the present stored resource through its original method and clear the pointer.
// Reference algorithm: src/hand/func_00146EE0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x90]; void * resource; };
void func_001BDB50(void *resource);
void func_0022B7F0(struct S *object)
{
    if(object->resource){func_001BDB50((char *)object->resource+0xF60);object->resource=0;}
}
