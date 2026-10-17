// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "common.h"
typedef union { qword q; float f; } U;
struct Item { unsigned char prefix[8]; void *object; unsigned char gap0C[4]; qword point; unsigned char tail[0x20]; };
struct Work { qword responses[4]; qword impulse; struct Item *items; };
int func_0013B500(void *object,int kind);
void func_002448F8(void *owner,int first,struct Work *work,int second,int side);
static inline qword Mulx(qword a,float g)
{
    U s;
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(g));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s.q));
    return r;
}
void func_002557E0(void *owner,int first,struct Work *work,int second,int side)
{
    qword saved=work->impulse;
    struct Item *other=&work->items[1-side];
    if(other->object && func_0013B500(other->object,0x55))
        work->impulse=Mulx(saved,0.01f);
    func_002448F8(owner,first,work,second,side);
    work->impulse=saved;
}
