// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"

struct CommandMask { unsigned char bytes[16]; };
struct CommandRecord;
struct CommandMask *func_00252D80(struct CommandMask *out,CRef *reference);
struct CommandRecord *func_002554C0(void *owner,const struct CommandMask *mask);
void func_00253468(void *owner,CRef *reference,int value,int mode);
void func_00254C00(struct CommandRecord *command,void *owner);

void func_002534C0(void *owner,CRef *reference,int value,int mode)
{
    struct CommandMask mask;
    struct CommandRecord *command;
    func_00252D80(&mask,reference);
    command=func_002554C0(owner,&mask);
    func_00253468(owner,reference,value,mode);
    func_00254C00(command,owner);
}
