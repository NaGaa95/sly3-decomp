// SLY3_CFLAGS: -Os -G0
struct TargetOwner { unsigned char opaque[0x1D50]; };
struct TargetBase { struct TargetOwner *object; };
struct TargetLink { struct TargetBase *base; int slot; unsigned char opaque08[0xC]; void *target; };
int func_0013B500(void *object, int identifier);
void func_0024BC70(void *target, void *link_base);
void func_001BE4F8(void *receiver, void *base)
{
    struct TargetLink *link = (struct TargetLink *)receiver;
    link->base = (struct TargetBase *)base;
    link->slot = -1;
    if (func_0013B500(((struct TargetBase *)base)->object, 0x34)) {
        link->target = (char *)link->base->object + 0x1D50;
        func_0024BC70(link->target, base);
    } else {
        link->target = 0;
    }
}
