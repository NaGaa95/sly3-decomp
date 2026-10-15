// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Private builtin callbacks with measured hidden CRef output and original lifetimes.
struct EvalFrame;
enum CRefTag { NullTag22 = 0x22 };
enum ScalarWordKind { Tag13Word };
class CRef {
public:
    short tag,word2;
    union { int integer;float real;void *pointer; } payload;
    CRef() { tag=-1; }
    CRef(CRefTag kind) { InitTag(kind); }
    CRef(int value,ScalarWordKind) {payload.integer=value;tag=0x13;}
    CRef(bool value) {tag=0x15;payload.integer=value;}
    CRef(const CRef &other);
    CRef &operator=(const CRef &other);
    void InitTag(int kind);
    void Decref();
    ~CRef() { Decref(); }
};
struct ListNode { CRef value;int word8;ListNode *next; };
typedef char CheckCRef8[(sizeof(CRef) == 8) ? 1 : -1];
typedef char CheckListNode16[(sizeof(ListNode) == 16) ? 1 : -1];
extern "C" void func_002BA780(ListNode **destination,ListNode *source);
extern "C" CRef func_00122880(int unused_count,CRef *arguments,EvalFrame *unused_frame,int operation)
{
    ListNode *target=(ListNode *)arguments[0].payload.pointer;
    if (operation==0x23) {
        target->value=arguments[1];
    } else if (arguments[1].tag==0x1D) {
        func_002BA780(&target->next,(ListNode *)arguments[1].payload.pointer);
    } else {
        func_002BA780(&target->next,0);
    }
    return CRef(NullTag22);
}
