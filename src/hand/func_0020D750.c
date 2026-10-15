// Forward the actual full128 position A1 and float F12 to the inherited initializer, then set the original scalar half and two complete packed defaults. The inherited helper consumes no incoming A2 input.
// Reference algorithm: src/hand/func_001885B8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
struct S {char prefix[0x18];float scale;int unknown;QWORD first;QWORD second;};
extern QWORD D_00325A30,D_00325A40;
void func_0020BC20(void *receiver,QWORD position,float scale);
void func_0020D750(struct S *p,QWORD position,float scale){func_0020BC20(p,position,scale);p->scale=0.5f;p->second=D_00325A30;p->first=D_00325A40;}
