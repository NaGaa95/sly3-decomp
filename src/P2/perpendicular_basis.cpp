// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };

// Reusable unpinned VU operations; scalar tests and basis construction are C++.
static inline qword Cross3(qword a,qword b)
{
    qword result;
    __asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1"
            : "=j"(result) : "j"(a),"j"(b));
    return result;
}
static inline qword Dot3(qword a,qword b)
{
    qword product,one;
    __asm__("vmul.xyz %0,%2,%3\n\t"
            "vaddw.x %1,$vf0,$vf0w\n\t"
            "vadday.x $ACC,%0,%0y\n\t"
            "vmaddz.x %0,%1,%0z"
            : "=j"(product),"=&j"(one) : "j"(a),"j"(b));
    return product;
}
static inline float XFloat(qword value)
{
    float x;
    __asm__("qmfc2.ni %0,%1" : "=r"(x) : "j"(value));
    return x;
}
static inline qword SqrtX(qword value)
{
    qword root;
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q"
            : "=j"(root) : "j"(value));
    return root;
}
static inline qword DivideByX(qword value,qword divisor)
{
    qword result;
    __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q"
            : "=j"(result) : "j"(divisor),"j"(value));
    return result;
}
extern "C" void func_0011FEA8(qword normal,qword try1,qword try2,M3 *output)
{
    qword first=Cross3(try1,normal);
    if (XFloat(Dot3(first,first))<0.0001f)
        first=Cross3(try2,normal);
    qword second=Cross3(normal,first);
    qword length1=SqrtX(Dot3(first,first));
    qword length2=SqrtX(Dot3(second,second));
    qword firstUnit=DivideByX(first,length1);
    qword secondUnit=DivideByX(second,length2);
    output->r[0]=firstUnit;
    output->r[1]=secondUnit;
}
