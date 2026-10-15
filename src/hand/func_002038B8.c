// Evaluate the original position and, when an output is provided, subtract the stored source position using one declared VU vector-subtract intrinsic.
// Reference algorithm: src/hand/func_001E1560.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
typedef unsigned int QWORD __attribute__((mode(TI)));
struct S { char prefix[0x260]; QWORD position; };
void func_0022E330(void *object,QWORD *output,int selector);
void func_002038B8(void *object,struct S *source,QWORD *output)
{
    QWORD value;
    func_0022E330(object,&value,0);
    if(output){QWORD difference; __asm__("vsub.xyzw %0, %1, %2" : "=j"(difference) : "j"(value), "j"(source->position)); *output=difference;}
}
