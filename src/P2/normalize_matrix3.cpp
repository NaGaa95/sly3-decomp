// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
struct MAT3 { qword a[3]; };

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
static inline qword Normalize3(qword value)
{
    return DivideByX(value,SqrtX(Dot3(value,value)));
}
extern "C" void func_0011C798(MAT3 *matrix)
{
    qword x=Normalize3(matrix->a[0]);
    qword cross=Cross3(x,matrix->a[1]);
    matrix->a[0]=x;
    qword z=Normalize3(cross);
    cross=Cross3(z,x);
    matrix->a[2]=z;
    matrix->a[1]=Normalize3(cross);
}
