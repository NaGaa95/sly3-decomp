// Reset the inherited object, apply the original kind-three record and flags, and enable the object.
// Reference algorithm: src/hand/func_001D4EC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00347FF0[];
void func_001F3BF8(void *object);
void func_001C8970(void *object,int kind,void *record,int flags);
void func_001F4670(void *object,int enabled);
void func_0020EDE0(void *object)
{
    func_001F3BF8(object);
    func_001C8970(object,3,D_00347FF0,0);
    func_001F4670(object,1);
}
