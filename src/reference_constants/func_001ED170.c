// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
void *func_001EB4C8(void *, qword, int);
int func_001ED170(void *context, qword point, int flags)
{
    return func_001EB4C8((char *)context + 0xD0, point, flags) != 0;
}
