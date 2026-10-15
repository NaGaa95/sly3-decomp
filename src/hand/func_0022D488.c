// Apply the explicit receiver/record/option update and forward it to the embedded state helper when the original state is5.24E400 consumes all three;1C3D18 consumes embedded A0 and record A1, supplied option A2 is caller-derived unused by its complete switch body.
// Reference algorithm: src/hand/func_00227728.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x1470]; int state; };
void func_0024E400(void *receiver,void *record,int option);
void func_001C3D18(void *receiver,void *record,int option);
void func_0022D488(struct S *p,void *record,int option){func_0024E400(p,record,option);if(p->state==5)func_001C3D18((char *)p+0xE40,record,option);}
