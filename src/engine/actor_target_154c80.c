// SLY3_CFLAGS: -Os -G0
typedef int ActorTargetVector __attribute__((mode(TI)));
struct ActorTargetObject;
struct ActorTargetMethod {
    short delta,unused;
    void (*kind)(void *,int);
};
struct ActorTargetControllerView {
    char before_object[0x10];
    struct ActorTargetObject *object;
    char before_target[0xF0-0x14];
    ActorTargetVector target;
};
struct ActorTargetOwnerView {
    char prefix[0xC];
    struct ActorTargetMethod *methods;
    char before_controller[0x1290-0x10];
    struct ActorTargetControllerView controller;
};
void func_00241338(struct ActorTargetObject *,float);
void func_00272628(struct ActorTargetControllerView *,int);
void func_002734E8(struct ActorTargetControllerView *,int);

void func_00154C80(struct ActorTargetOwnerView *owner,struct ActorTargetObject *object,ActorTargetVector target)
{
    struct ActorTargetMethod *method;
    func_00241338(object,0.25f);
    owner->controller.object=object;
    owner->controller.target=target;
    func_00272628(&owner->controller,0);
    method=&owner->methods[99];
    method->kind((char *)owner+method->delta,7);
    func_002734E8(&owner->controller,7);
}
