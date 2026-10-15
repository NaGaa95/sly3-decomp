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
extern "C" CRef func_001269D8(int selector,int count,CRef *arguments,EvalFrame *frame);
extern "C" CRef func_00126E08(int count,CRef *arguments,EvalFrame *frame)
{
    CRef result;
    result=func_001269D8(0x83,count,arguments,frame);
    return result;
}
extern "C" CRef func_00126E88(int count,CRef *arguments,EvalFrame *frame)
{
    CRef result;
    result=func_001269D8(0x84,count,arguments,frame);
    return result;
}
