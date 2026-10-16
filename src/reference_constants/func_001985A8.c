// SLY3_CFLAGS: -Os -G0
#include "wait_bind_api.h"
int func_001985F0(void *, void *);
void *func_002387A8(void *, int);
void func_001985A8(char *p, void *context)
{
    if (func_001985F0(p, context))
        func_00197838((struct WaitBindState *)func_002387A8(p + 0x29C, 0xD3), 0, 0, 0);
}
