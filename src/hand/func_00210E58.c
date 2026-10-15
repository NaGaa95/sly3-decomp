// Forward actual receiver A0/enabled A1, transition original state2 to3 and store the original conditional result. Both callees consume the two supplied actual inputs.
// Reference algorithm: src/hand/func_00144268.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x8]; int state; char unknown_C[0x10]; int result; };
void func_00210ED8(void *receiver,int enabled);
void func_00210C90(void *receiver,int state);
void func_00210E58(struct S *p,int enabled){func_00210ED8(p,enabled);if(p->state==2)func_00210C90(p,3);if(enabled)p->result=2;else p->result=3;}
