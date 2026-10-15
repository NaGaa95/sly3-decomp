// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
/* EE (single-float EABI) stdarg, from gcc's va-mips.h */
typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
struct CRef { short tagk; short reserved; union { int n; float value; void *pointer; } payload; };
struct CRef *func_0024B068(struct CRef *ret, int c, struct CRef *aref, int *aotype, void **outputs);
struct CRef *func_0024B2B8(struct CRef *ret, int c, struct CRef *aref, int *aotype, ...)
{
    va_list ap;
    void *outputs[32];
    int i;
    va_start(ap, aotype);
    for (i = 0; i < c; i++) {
        ap += 8;
        outputs[i] = *(void **)(ap - 8);
    }
    func_0024B068(ret, c, aref, aotype, outputs);
    return ret;
}
