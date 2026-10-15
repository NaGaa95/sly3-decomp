// Update the inherited object and transform its stored128-bit value into the output field with absent secondary owner.
// Reference algorithm: src/hand/func_00146EE0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int QWORD __attribute__((mode(TI)));
struct S { char prefix[0x240]; QWORD output; QWORD input; };
void func_0023D0E8(struct S *object);
QWORD func_001C9428(struct S *object, void *owner, QWORD value);
void func_0024E370(struct S *object)
{
    func_0023D0E8(object);
    object->output = func_001C9428(object, 0, object->input);
}
