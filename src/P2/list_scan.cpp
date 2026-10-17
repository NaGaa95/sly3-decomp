// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct Method { short delta,unused; void (*method)(void); };
struct ListNode { unsigned char prefix[0xC]; Method *methods; unsigned char gap10[0x24]; int field34; unsigned char gap38[0xC]; ListNode *next; };
static inline void CallNode(ListNode *node,int slot)
{
    ((void (*)(void *))node->methods[slot].method)((char *)node+node->methods[slot].delta);
}
extern "C" ListNode *D_00479DA4;
extern "C" int func_00237120(ListNode *node);
extern "C" void func_002BF1C8(void *object,int flags);
class CleanupScope {
public:
    CleanupScope() {}
    ~CleanupScope() { func_002BF1C8(this,2); }
};
extern "C" void func_00235FF8(void)
{
    CleanupScope scope;
    ListNode *node=D_00479DA4;
    while(node && !node->field34) {
        if(func_00237120(node))
            CallNode(node,8);
        node=node->next;
    }
}
