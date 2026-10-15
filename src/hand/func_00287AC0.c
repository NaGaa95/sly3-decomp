// Reset the inherited object and apply the original global 128-bit reference value.
// Reference algorithm: src/hand/func_00146EE0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int QWORD __attribute__((mode(TI)));
extern QWORD D_00317560;
void func_0023C580(void *object);
void func_0023ED58(void *object, QWORD value);
void func_00287AC0(void *object)
{
    func_0023C580(object);
    func_0023ED58(object, D_00317560);
}
