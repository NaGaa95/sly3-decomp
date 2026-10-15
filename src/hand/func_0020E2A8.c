// Initialize the inherited receiver with the explicit128-bit position and float gravity, then apply the original control and stored vector defaults.
// Reference algorithm: src/hand/func_001B4438.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int QWORD __attribute__((mode(TI)));
extern QWORD D_00325AC0;
struct S { char prefix[0x18];float control;char reserved[0xA0-0x1C];QWORD position; };
void func_0020BC20(struct S *p,QWORD position,float gravity);
void func_0020E2A8(struct S *p,QWORD position,float gravity){func_0020BC20(p,position,gravity);p->control=5.0f;p->position=D_00325AC0;}
