// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"
struct KEY;
struct Subject { unsigned char prefix[0x1C]; int mode; int *key; };
extern unsigned char D_00468D30[];
CRef *func_002BC010(CRef *output, struct KEY *key, unsigned char *buffer);
int func_00210DE0(struct Subject *subject)
{
    switch(subject->mode) {
    case 2:
        return 1;
    case 1:
        if(subject->key && *subject->key) {
            CRef value;
            int result;
            func_002BC010(&value,(struct KEY *)subject->key,D_00468D30);
            result=value.payload.integer;
            func_0012BC20(&value);
            return result^1;
        }
    default:
        return 0;
    }
}
