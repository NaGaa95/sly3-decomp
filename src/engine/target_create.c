// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
extern char D_00475480[];
void func_00166548(void *owner);
void *func_001F4AD0(void *game,int index);
void *func_0017E1B8(void *game,int flags,int key,void *context);
void func_00168358(void *owner,void *target,Qword value);
struct CreateOwner { unsigned char prefix[0x41C]; int kind; void *target; unsigned char gap424[0x430-0x424]; Qword vector; };
void func_001682A8(struct CreateOwner *owner,int kind)
{
    owner->kind=kind;
    if(kind==-1) {
        owner->target=0;
        func_00166548(owner);
        return;
    }
    if(kind==0x20) owner->target=func_001F4AD0(D_00475480,0);
    else owner->target=func_0017E1B8(D_00475480,5,kind,0);
    func_00168358(owner,owner->target,owner->vector);
}
