// Reference: Sly 2 src/lib/dptofp.c; target Sly 3 0x0029CC20.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
typedef struct { int class; unsigned int sign; int normal_exp; int pad; unsigned long fraction; } fp_number_type;
float __make_fp(int, unsigned int, int, unsigned int);
void __unpack_d(void *, fp_number_type *);
float dptofp(double arg_a)
{
    fp_number_type in;
    unsigned int tmp;
    union { double value; unsigned long raw; } au;
    au.value = arg_a;
    __unpack_d(&au, &in);
    tmp = in.fraction >> 30;
    if ((in.fraction & 0x3fffffff) != 0) tmp |= 1;
    return __make_fp(in.class, in.sign, in.normal_exp, tmp);
}
