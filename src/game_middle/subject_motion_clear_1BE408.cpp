// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int SubjectMotionVector __attribute__((mode(TI)));
struct SubjectMotionMethod {
    short adjustment,padding;
    union { void (*action)(void *,int,int);void (*vector)(void *,SubjectMotionVector); };
};
struct SubjectMotionTarget {
    char prefix[12];SubjectMotionMethod *methods;
    char before_acceleration[0x1A0-0x10];float acceleration[3];
};
struct SubjectMotionOwner { char prefix[0x40];SubjectMotionTarget *target; };
extern "C" SubjectMotionVector D_00317560;
extern "C" void func_0023EBF8(void *,int);
extern "C" void func_001BE408(SubjectMotionOwner *owner) {
    SubjectMotionTarget *target=owner->target;
    if(target) {
        SubjectMotionMethod *method=&target->methods[94];
        method->action((char *)target+method->adjustment,0x3F,1);
        func_0023EBF8(target,1);
        float *acceleration=target->acceleration;
        acceleration[2]=0.0f;
        acceleration[1]=0.0f;
        acceleration[0]=0.0f;
        method=&target->methods[40];
        method->vector((char *)target+method->adjustment,D_00317560);
        method=&target->methods[41];
        method->vector((char *)target+method->adjustment,D_00317560);
    }
}
