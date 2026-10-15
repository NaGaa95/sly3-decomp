// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
static inline qword PackXYZ(float x,float y,float z)
{
    qword result,scratch;
    __asm__("mfc1 %0,%2\n\t"
            "mfc1 %1,%3\n\t"
            "pextlw %0,%1,%0\n\t"
            "mfc1 %1,%4\n\t"
            "pcpyld %0,%1,%0"
            : "=&r"(result),"=&r"(scratch) : "f"(x),"f"(y),"f"(z));
    return result;
}
extern "C" void func_0011EB28(float *sine,float *cosine,float angle);
extern "C" qword func_0011FD70(float pan,float radius,float height)
{
    union { qword q; float f[4]; } value;
    float sine,cosine;
    func_0011EB28(&sine,&cosine,pan);
    value.q=PackXYZ(cosine*radius,sine*radius,height);
    return value.q;
}
