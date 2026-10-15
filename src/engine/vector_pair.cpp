// SLY3_CFLAGS: -Os -G0 -fno-exceptions
typedef int PairPackedWord __attribute__((mode(TI)));
struct Node;
class CRef {
public:
    short tag;
    short word2;
    union { int word; float real; void *pointer; } payload;
    CRef(Node *node);
    void InitTag(int kind);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(float value);
    void SetTag(int kind) { Decref(); InitTag(kind); }
};
struct Node;
extern "C" {
Node *func_002BA6B8();
void func_002BA760(Node **slot,Node *node);
void func_002BA780(Node **slot,Node *node);
void func_002BA840(Node *node,int flags);
float func_00120080(PairPackedWord first,PairPackedWord second,void *vector_output);
}
struct Node {
    CRef reference; int word8; Node *next;
    void SetNext(Node *node) { func_002BA780(&next,node); }
};
struct PairNodeReference {
    Node *pointer;
    void Set(Node *node) { func_002BA760(&pointer,node); }
    ~PairNodeReference() {
        Node *node=pointer;
        if(node && --node->reference.word2==0)
            func_002BA840(node,3);
    }
    Node *operator->() { return pointer; }
};
extern "C" CRef func_00124A58(int unused_count,CRef *arguments,void *unused_frame)
{
    PairNodeReference result;
    result.Set(func_002BA6B8());
    result->SetNext(func_002BA6B8());
    CRef *vector=&result->next->reference;
    vector->SetTag(0x18);
    result->reference=func_00120080(*(PairPackedWord *)arguments[0].payload.pointer,
                                  *(PairPackedWord *)arguments[1].payload.pointer,
                                  vector->payload.pointer);
    return CRef(result.pointer);
}
