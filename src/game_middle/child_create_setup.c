// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, word2; void *function; };
struct ChildTable {
    unsigned char prefix0[0x40];
    struct Method begin;
    unsigned char prefix1[0x118 - 0x48];
    struct Method setBounds;
    unsigned char prefix2[0x140 - 0x120];
    struct Method setStart;
    struct Method setEnd;
};
struct Child {
    unsigned char prefix[0xC];
    struct ChildTable *methods;
};
extern char D_00317490[];
extern qword D_00317560;
void *func_001FBE30(void *resource, int flag);
void func_001C7A00(void *receiver, void *parent, int flags);
void *func_001EB058(void *resource)
{
    struct Child *child;
    if (!resource)
        return 0;
    child = func_001FBE30(resource, 0);
    if (child) {
        func_001C7A00(child, 0, 0);
        ((void (*)(void *))child->methods->begin.function)((char *)child + child->methods->begin.adjustment);
        ((void (*)(void *, void *))child->methods->setBounds.function)((char *)child + child->methods->setBounds.adjustment, D_00317490);
        ((void (*)(void *, qword))child->methods->setStart.function)((char *)child + child->methods->setStart.adjustment, D_00317560);
        ((void (*)(void *, qword))child->methods->setEnd.function)((char *)child + child->methods->setEnd.adjustment, D_00317560);
    }
    return child;
}
