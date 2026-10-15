// Reset the stored selection and float default, then apply both original absent input selectors.
// Reference algorithm: src/hand/func_0014C6A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Default {float value;};
extern struct Default D_0036BBD8;
struct S { char unknown_0[0x38]; int selection; float value; };
void func_0021ED28(struct S *p,int first,int second);
void func_0021EBA8(struct S *p){p->selection=-1;p->value=D_0036BBD8.value;func_0021ED28(p,-1,-1);}
