// Dispatch the full seven-input query to the original mode-specific implementation with every128-bit and pointer argument explicit.
// Reference algorithm: src/hand/func_001803A8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int QWORD __attribute__((mode(TI)));
struct S { char prefix[0xD0]; int mode; };
void func_0022E5B0(struct S *, QWORD, void *, void *, void *, float *, float *);
void func_0022E938(struct S *, QWORD, void *, void *, void *, float *, float *);
void func_0022EA50(struct S *object, QWORD value, void *transform, void *position, void *direction, float *progress, float *length)
{
    if (!object->mode) func_0022E5B0(object, value, transform, position, direction, progress, length);
    else func_0022E938(object, value, transform, position, direction, progress, length);
}
