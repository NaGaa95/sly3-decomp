// Release the actual retained member, unlink the receiver, and honor its original destructor flags.
// Original accessed layouts and complete argument flow are independently verified; nominal type names remain provisional.
// SLY3_CFLAGS: -Os -G0
struct Member {
    int references;
};
struct S {
    char prefix[8];
    struct Member *member;
};
void func_002BACE0(void *receiver,int flags);
void func_002B4A88(void *receiver);
void func_0011E1F0(void *pool,void *object);
extern char D_004D2E38[];
void func_002BB8B8(struct S *p,int flags) {
    struct Member *member=p->member;
    if(member) {
        if(--member->references==0)func_002BACE0(member,3);
    }
    func_002B4A88(p);
    if(flags&1)func_0011E1F0(D_004D2E38,p);
}
