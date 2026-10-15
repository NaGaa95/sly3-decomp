// Store the explicit float and three-coordinate vector in the receiver fields.
// Reference algorithm: src/hand/func_001A15B0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V { float x,y,z; };
struct S { char prefix[0x1D4]; float value; struct V vector; };
void func_00248E98(struct S *object,struct V *vector,float value)
{
    object->value=value;
    object->vector=*vector;
}
