// Clear the original selection when its duration expires. Receiver and sentinel selection are explicit; the ordered float comparison retains original NaN behavior under the selected matching profile.
// Reference algorithm: src/hand/func_002313F0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x4F4]; int selection; float started; float duration; };
extern float D_0036BB98;
void func_00215388(void *receiver,int selection);
void func_002155F0(struct S *p){if(p->selection!=-1&&D_0036BB98-p->started>p->duration)func_00215388(p,-1);}
