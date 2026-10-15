// Store all four explicit integer/float notification fields in their original Sly3 layout.
// Reference algorithm: src/hand/func_001F5860.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x45C]; int first; int second; float value; int third; };
void func_00219448(struct S *object,int first,int second,int third,float value)
{
    object->first=first;object->second=second;object->value=value;object->third=third;
}
