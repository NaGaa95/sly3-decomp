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
extern "C" unsigned char D_0036C700[];
extern "C" int func_001852E0(void *context);
extern "C" void func_00185328(void *context,int value);
extern "C" CRef func_001276B8(int unused_argument_count,CRef *arguments,EvalFrame *unused_frame)
{
    CRef result(NullTag22);
    int delta=arguments->payload.integer;
    void *context=D_0036C700;
    int current=func_001852E0(context);
    func_00185328(context,(int)((unsigned int)current+(unsigned int)delta));
    return result;
}
