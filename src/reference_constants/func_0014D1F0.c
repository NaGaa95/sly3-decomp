// SLY3_CFLAGS: -Os -G0
#include "reset_source_link_api.h"
extern char D_00475480[];
void func_0013CD10(void *,void *);
void func_0014D1F0(void *receiver,void *source)
{
    char *object=(char *)receiver;
    if(source!=*(void **)(object+0x1E8)) {
        *(void **)(object+0x1E8)=source;
        func_0013CD10(D_00475480,object);
    }
}
