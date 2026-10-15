// Store the resource looked up by the original kind five and identifier0x6F1.
// Reference algorithm: src/hand/func_001A5BF0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x4E4C]; void *resource; };
void *func_0017E1B8(struct S *object,int kind,int id,void *owner);
void func_0025DD00(struct S *object)
{
    object->resource=func_0017E1B8(object,5,0x6F1,0);
}
