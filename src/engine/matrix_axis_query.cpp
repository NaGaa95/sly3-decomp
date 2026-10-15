// SLY3_CFLAGS: -Os -G0 -fno-exceptions
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
struct MATRIX3;
struct VECTOR;
extern "C" void func_0011D0B8(MATRIX3 *matrix,float *angle,VECTOR *axis);
extern "C" CRef func_00124E60(int unused_count,CRef *arguments,void *unused_frame)
{
    PairNodeReference result;
    struct { float angle; unsigned char unused_tail[8]; } scalar;
    result.Set(func_002BA6B8());
    result->SetNext(func_002BA6B8());
    CRef *axis=&result->next->reference;
    axis->SetTag(0x18);
    func_0011D0B8((MATRIX3 *)arguments[0].payload.pointer,&scalar.angle,
                   (VECTOR *)axis->payload.pointer);
    result->reference=scalar.angle;
    return CRef(result.pointer);
}
