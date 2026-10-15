// Submit the original seven explicit SDK command fields with command2 and receiver value.
// Reference algorithm: src/hand/func_0019ABB8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x44]; int value; };
int func_00291CE8(unsigned int signature,int command,int value,int a,int b,int c,int d);
int func_00246538(struct S *object)
{
    return func_00291CE8(0x524B5553u,2,object->value,0,0,0,0);
}
