// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions
#include "../P2/vector_intrinsics.h"
struct AdditiveTaskMethod {
    short delta;
    short unused;
    void (*method)();
};
struct AdditiveTaskProvider {
    unsigned char prefix[0x18];
    AdditiveTaskMethod *methods;
};
struct AdditiveTaskRuntime {
    unsigned char prefix[0xC0];
    qword lower_value;
    unsigned char unusedD0[16];
    qword upper_value;
};
struct AdditiveTaskView {
    unsigned char prefix[8];
    AdditiveTaskRuntime *runtime;
    unsigned char unusedC[0x10];
    AdditiveTaskProvider *provider;
    qword offset;
};
extern "C" void func_0012F318(void *);
static __inline__ void AddOffset(qword *destination, const qword *offset)
{
    qword sum;
    asm("vadd.xyzw %0,%1,%2" : "=j"(sum) : "j"(*destination), "j"(*offset));
    *destination = sum;
}
extern "C" void func_0012FDB8(void *receiver)
{
    AdditiveTaskView *task = (AdditiveTaskView *)receiver;
    AdditiveTaskProvider *provider = task->provider;
    if (provider) {
        ((void (*)(void *))provider->methods[4].method)
            ((char *)provider + provider->methods[4].delta);
        AddOffset(&task->runtime->lower_value, &task->offset);
        AddOffset(&task->runtime->upper_value, &task->offset);
    } else {
        func_0012F318(task);
    }
}
extern "C" void func_0012FE30(void *receiver, qword *output,
                                  void *derivative, float time)
{
    AdditiveTaskView *task = (AdditiveTaskView *)receiver;
    AdditiveTaskProvider *provider = task->provider;
    ((void (*)(void *, qword *, void *, float))provider->methods[5].method)
        ((char *)provider + provider->methods[5].delta, output, derivative, time);
    if (output)
        AddOffset(output, &task->offset);
}
