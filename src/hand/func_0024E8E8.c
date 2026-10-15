// Convert the explicit128-bit vector to its float value and apply the result to the receiver.
// Reference algorithm: src/hand/func_001A5BF0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int QWORD __attribute__((mode(TI)));
float func_001205C8(QWORD value);
void func_0024E878(void *object,float value);
void func_0024E8E8(void *object,QWORD value)
{
    func_0024E878(object,func_001205C8(value));
}
