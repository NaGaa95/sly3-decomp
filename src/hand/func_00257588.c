// Compare the inverse explicit enabled state with the stored state, set the original update flag, and increment the embedded record counter through its original helper.
// Reference algorithm: src/hand/func_001715B8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x4C0]; int state; };
void func_00259D10(void *record);
void func_00257588(struct S *object,int enabled)
{
    int state=!enabled;
    if(state!=object->state){object->state=1;func_00259D10((char *)object+0x4B0);}
}
