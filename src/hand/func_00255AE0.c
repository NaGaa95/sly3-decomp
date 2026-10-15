// Construct the original command using all eight GP inputs, two full128 vectors, and ninth nullable stack output. Complete240CB0 consumes every declared argument; it consumes no incoming float register.
// Reference algorithm: src/hand/func_001DA728.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
extern QWORD D_00317560;
void func_00240CB0(void *receiver,int option,void *owner,int flags,int identifier,int active,QWORD position,QWORD direction,void *output);
void func_00255AE0(void *owner,void *receiver){func_00240CB0(receiver,0,owner,0x40000,50,1,D_00317560,D_00317560,0);}
