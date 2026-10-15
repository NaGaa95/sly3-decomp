// Initialize the inherited object and set its deadline to the original global time plus one.
// Reference algorithm: src/hand/func_00184F98.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern float D_0036BB98;
struct S { char prefix[0x60]; float deadline; };
void func_001C78A0(struct S *object);
void func_0021AD38(struct S *object)
{
    func_001C78A0(object);
    object->deadline=D_0036BB98+1.0f;
}
