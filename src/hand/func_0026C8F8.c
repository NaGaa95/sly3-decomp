// Update the inherited selection using the explicit integer input and select the enabled state from the original resource predicate.
// Reference algorithm: src/hand/func_001BBEA8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_001F4548(void *object,int selection);
int func_001F4350(void *object,int selection);
void func_0026CD30(void *object,int enabled);
void func_0026C8F8(void *object,int selection)
{
    func_001F4548(object,selection);
    if(func_001F4350(object,-1))func_0026CD30(object,1);
    else func_0026CD30(object,0);
}
