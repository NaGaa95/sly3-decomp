// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct Pose { unsigned char prefix[0x10]; void *space; unsigned char gap14[0x34]; void *matrix; unsigned char gap4C[4]; void *source; unsigned char gap54[0x1FC]; qword first; qword second; qword third; };
extern qword D_00317560;
void func_001F3BC8(void *object);
qword func_001C9428(void *source,void *object,qword point);
qword func_0028E910(void *source,void *destination,qword point);
void func_00241B60(void *object);
static inline qword Mulx(qword a,float g)
{
    U s;
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(g));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s.q));
    return r;
}
void func_0024D920(struct Pose *pose)
{
    func_001F3BC8(pose);
    pose->second=pose->first=func_001C9428(pose->space,pose,D_00317560);
    pose->third=Mulx(func_0028E910(pose->source,pose->matrix,D_00317560),-1.0f);
    func_00241B60(pose);
}
