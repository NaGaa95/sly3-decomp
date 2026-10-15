// Enable the original receiver state and apply the secondary enable only when its selection is absent.
// Reference algorithm: src/hand/func_0020A010.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x68]; int selection; };
void func_00261050(struct S *object,int enabled);
void func_00261070(struct S *object,int enabled);
void func_00260FE8(struct S *object)
{
    func_00261050(object,1);
    if(object->selection==-1)func_00261070(object,1);
}
