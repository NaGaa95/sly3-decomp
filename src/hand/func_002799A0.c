// Subtract the explicit delta, clamp the stored value to zero, and return the observed result word.
// Reference algorithm: src/hand/func_00129480.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x134]; int value; };
int func_002799A0(struct S *object,int delta)
{
    int value=object->value-delta;
    if(value<0)value=0;
    object->value=value;return value;
}
