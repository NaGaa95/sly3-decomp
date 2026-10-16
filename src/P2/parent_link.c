// SLY3_CFLAGS: -Os -G0
struct ParentLinkPrefix {
    unsigned char beforeParent[0x10];
    struct ParentLinkPrefix *parent;
    unsigned char beforeRuntime[0xDC-0x14];
    void *runtime;
};
struct ParentLinkOwner {
    unsigned char beforeRuntime[0xDC];
    void *runtime;
    unsigned char beforeSelection[0x2E4-0xE0];
    void *selected;
    struct ParentLinkPrefix *resolved;
};
struct ParentLinkPrefix *func_001C7D60(void *object);
void func_0013C388(void *game,void *source,void *target,int mode);
void func_0023DD40(void *owner);
extern unsigned char D_00475480[];
void func_0024F3B8(void *receiver,void *input,int active)
{
    struct ParentLinkOwner *owner=receiver;
    struct ParentLinkPrefix *other=func_001C7D60(input);
    while (other && !other->runtime) other=other->parent;
    if (active) {
        owner->selected=input;
        owner->resolved=other;
    } else {
        owner->selected=0;
        owner->resolved=0;
    }
    if (owner->runtime && other && other->runtime)
        func_0013C388(D_00475480,owner->runtime,other->runtime,active?1:2);
    func_0023DD40(owner);
}
