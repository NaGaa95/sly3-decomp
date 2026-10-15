// Reference: Sly 2 src/lib/func_0024A098.c; target Sly 3 0x002A8AC0.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
/* libm finitef */
typedef union { float value; unsigned int word; } ieee_float_shape_type;
#define GET_FLOAT_WORD(i,d) do { ieee_float_shape_type gf_u; gf_u.value = (d); (i) = gf_u.word; } while (0)
int func_002A8AC0(float x)
{
    int ix;
    GET_FLOAT_WORD(ix, x);
    return (int)((unsigned int)((ix & 0x7fffffff) - 0x7f800000) >> 31);
}
