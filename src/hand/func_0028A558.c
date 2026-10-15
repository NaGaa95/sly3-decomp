// Create the original two-slot record with selection zero and store its default128-bit value.
// Reference algorithm: src/hand/func_00185BF8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int QWORD __attribute__((mode(TI)));
extern QWORD D_00317530;
struct R { char prefix[0x20]; QWORD value; };
struct R *func_0028A480(void *object,int selection,int size);
void func_0028A558(void *object)
{
    func_0028A480(object,0,2)->value=D_00317530;
}
