// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Private adjacent builtin results use the proven hidden CRef output ABI.
struct EvalFrame;
enum CRefTag { NullTag22 = 0x22 };
enum ScalarWordKind { Tag13Word };
class CRef {
public:
    short tag,word2;
    union { int integer;float real;void *pointer; } payload;
    CRef(CRefTag kind) { InitTag(kind); }
    CRef(int value, ScalarWordKind) { payload.integer=value;tag=0x13; }
    CRef(const CRef &other);
    void Decref();
    ~CRef() { Decref(); }
    void InitTag(int kind);
};
struct ListNode { CRef value;int word8;ListNode *next; };
typedef char CheckCRef8[(sizeof(CRef) == 8) ? 1 : -1];
typedef char CheckListNode16[(sizeof(ListNode) == 16) ? 1 : -1];
extern "C" CRef func_001274E0(int unused_argument_count, CRef *unused_arguments, EvalFrame *unused_frame)
{
    return CRef(NullTag22);
}
extern "C" CRef func_00127510(int unused_argument_count, CRef *arguments, EvalFrame *unused_frame)
{
    int value=-1;
    ListNode *node=0;
    if (arguments->tag)
        node=(ListNode *)arguments->payload.pointer;
    while (node) {
        value &= node->value.payload.integer;
        node=node->next;
    }
    return CRef(value,Tag13Word);
}
extern "C" CRef func_00127560(int unused_argument_count, CRef *arguments, EvalFrame *unused_frame)
{
    int value=0;
    ListNode *node=0;
    if (arguments->tag)
        node=(ListNode *)arguments->payload.pointer;
    while (node) {
        value |= node->value.payload.integer;
        node=node->next;
    }
    return CRef(value,Tag13Word);
}
