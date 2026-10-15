// Apply the original index-zero global resource to the explicit receiver.
// Reference algorithm: src/hand/func_001F3868.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
void *func_001F4AD0(void *global,int index);
void func_00225EE8(void *object,void *resource);
void func_00226010(void *object)
{
    func_00225EE8(object,func_001F4AD0(D_00475480,0));
}
