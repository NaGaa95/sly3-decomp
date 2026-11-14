// Sly 2 counterpart: litodp (decomp src/lib/litodp.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorg
typedef unsigned long fractype;
typedef int SItype;
typedef enum { CLASS_SNAN, CLASS_QNAN, CLASS_ZERO, CLASS_NUMBER, CLASS_INFINITY } fp_class_type;
typedef struct {
    fp_class_type class;
    unsigned int sign;
    int normal_exp;
    union { fractype ll; } fraction;
} fp_number_type;
double __pack_d(fp_number_type *);

double func_0029CA00(SItype arg_a)
{
    fp_number_type in;

    in.class = CLASS_NUMBER;
    in.sign = arg_a < 0;
    if (!arg_a)
    {
        in.class = CLASS_ZERO;
    }
    else
    {
        in.normal_exp = 52 + 8;
        if (in.sign)
        {
            if (arg_a == (SItype)0x80000000)
            {
                return -2147483648.0;
            }
            in.fraction.ll = (-arg_a);
        }
        else
            in.fraction.ll = arg_a;

        while (in.fraction.ll < (1L << (52 + 8)))
        {
            in.fraction.ll <<= 1;
            in.normal_exp -= 1;
        }
    }
    return __pack_d(&in);
}
