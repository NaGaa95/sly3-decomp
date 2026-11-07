// Sly 2 counterpart: fptodp (decomp src/lib/fptodp.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef unsigned int fractype;
typedef enum { CLASS_SNAN, CLASS_QNAN, CLASS_ZERO, CLASS_NUMBER, CLASS_INFINITY } fp_class_type;
typedef struct {
    fp_class_type class;
    unsigned int sign;
    int normal_exp;
    union { fractype ll; } fraction;
} fp_number_type;
typedef union {
    float value;
} FLO_union_type;

void __unpack_f(FLO_union_type *src, fp_number_type *dst);
double __make_dp(fp_class_type class, unsigned int sign, int exp, unsigned long frac);

/* 2 instructions differ: target `swc1 f12; jal; daddu a1,sp` - here swc1 lands in the jal delay slot */
double func_0029CF10(float arg_a)
{
    fp_number_type in;
    float au;

    au = arg_a;
    __unpack_f((FLO_union_type *)&au, &in);
    return __make_dp(in.class, in.sign, in.normal_exp, ((unsigned long)in.fraction.ll) << 30);
}
