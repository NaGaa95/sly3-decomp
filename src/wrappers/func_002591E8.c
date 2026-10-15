// SLY3_CFLAGS: -Os -G0

typedef int qword __attribute__((mode(TI)));
struct CylinderLimits;
extern int func_0011FB88(const struct CylinderLimits *, qword);
int func_002591E8(void *a0, qword point)
{
    return func_0011FB88((const struct CylinderLimits *)((char *)a0 + 112), point);
}
