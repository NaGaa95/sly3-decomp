// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
struct MATRIX4;
static inline float LengthSquaredXYZ(qword value)
{
    qword product,one;
    __asm__("vmul.xyz %0,%2,%2\n\t"
            "vaddw.x %1,$vf0,$vf0w\n\t"
            "vadday.x $ACC,%0,%0y\n\t"
            "vmaddz.x %0,%1,%0z"
            : "=j"(product),"=&j"(one) : "j"(value));
    float result;
    __asm__("mtc1 %1,%0" : "=f"(result) : "r"(product));
    return result;
}
static inline float SqrtScalar(float value)
{
    float root;
    __asm__("sqrt.s %0,%1" : "=&f"(root) : "f"(value));
    return root;
}
extern "C" float func_0011DF08(const MATRIX4 *matrix)
{
    const qword *columns=(const qword *)matrix;
    float a=LengthSquaredXYZ(columns[0]);
    float b=LengthSquaredXYZ(columns[1]);
    float c=LengthSquaredXYZ(columns[2]);
    float largest;
    if (b<a && c<a) largest=a;
    else if (c<b) largest=b;
    else largest=c;
    return SqrtScalar(largest);
}
