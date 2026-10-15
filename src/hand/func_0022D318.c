// Use the explicit receiver to compute/store all128 position bits, then initialize the embedded record with actual GP A0..A3 and float F12.250600 consumes receiver only through18B1E0;1B7268 saves all four GP inputs and the float scale.
// Reference algorithm: src/hand/func_001A3078.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
struct S { char unknown_0[0x240]; QWORD position; char unknown_250[0x1390]; int state; };
QWORD func_00250600(void *receiver);
void func_001B7268(float scale,void *record,int option,void *resource,void *context);
void func_0022D318(struct S *p){if(p->state){p->position=func_00250600(p);func_001B7268(1.0f,(char *)p+0x320,1,0,0);}}
