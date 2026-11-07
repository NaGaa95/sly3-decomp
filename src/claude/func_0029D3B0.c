// Sly 2 counterpart: __eh_rtime_match (decomp src/lib/__eh_rtime_match.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
// SLY3_SAVES: sd
typedef void *(*__eh_matcher)(void *, void *, void *);
typedef struct { __eh_matcher match_function; short language; short version; } __eh_info;
void **__get_eh_info(void);
int func_0029D3B0(void *rtime)
{
    void *info;
    __eh_matcher matcher;
    void *ret;
    info = *(__get_eh_info());
    matcher = ((__eh_info *)info)->match_function;
    if (!matcher)
        goto none;
    ret = (*matcher)(info, rtime, (void *)0);
    return (ret != 0);
none:
    return 0;
}
