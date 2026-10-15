// Initialize the original clock, packed position/direction, scalar weight and aligned float3x4 basis.
// Actual receiverA0, full128-bit valueA1 and weightF12 are explicit.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
struct MATRIX3 {float mat[3][4];} __attribute__((aligned(16)));struct S {char prefix[0x14];float timestamp,duration;int unused;float weight;char gap[0xC];QWORD direction;struct MATRIX3 basis;QWORD first,second;};
extern float D_0036BB98;extern QWORD D_00325A00;extern struct MATRIX3 D_00317490;
void func_0020BC20(struct S *p,QWORD value,float weight){p->duration=1.0f;p->timestamp=D_0036BB98;p->weight=weight;p->direction=D_00325A00;p->second=value;p->first=value;p->basis=D_00317490;}
