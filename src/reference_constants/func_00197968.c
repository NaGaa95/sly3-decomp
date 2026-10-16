// SLY3_CFLAGS: -Os -G0
#include "wait_bind_api.h"
void func_00238980(void *);
void func_00238A38(void *);
void func_00252FC0(void *, int);
void func_00197968(char *p)
{
    func_00238980(p);
    func_00238A38(p);
    func_00197838((struct WaitBindState *)p, 0, 0, 0);
    func_00252FC0(*(void **)(p+0x10), 0x35);
}
