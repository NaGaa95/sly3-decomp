// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// func_001254B8: script builtin: PosSmooth (func_00120C80) on two position arguments, a time and an SMP, returning
// the list (new position, velocity). CRef/Node modelling follows src/engine/vector_pair.cpp.
typedef long long qword __attribute__((mode(TI)));
struct Node;
class CRef {
public:
    short tag;
    short word2;
    union { int word; float real; void *pointer; } payload;
    CRef(Node *node);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(float value);
    CRef &operator=(qword value);
    void SetVector(qword *pv) __asm__("func_0012B400");
};
struct Node;
extern "C" {
Node *func_002BA6B8();
void func_002BA760(Node **slot, Node *node);
void func_002BA780(Node **slot, Node *node);
void func_002BA840(Node *node, int flags);
CRef func_0012BAE8(CRef *reference);
qword func_00120C80(qword posCur, qword posTarget, float dt, void *psmp, qword *pv);
}
struct Node {
    CRef reference; int word8; Node *next;
    void SetNext(Node *node) { func_002BA780(&next, node); }
};
struct NodeRef {
    Node *pointer;
    void Set(Node *node) { func_002BA760(&pointer, node); }
    ~NodeRef() {
        Node *node = pointer;
        if (node && --node->reference.word2 == 0)
            func_002BA840(node, 3);
    }
    Node *operator->() { return pointer; }
};
static inline CRef Pair(qword a, qword *pb)
{
    NodeRef result;
    result.Set(func_002BA6B8());
    result->reference = a;
    result->SetNext(func_002BA6B8());
    result->next->reference.SetVector(pb);
    return CRef(result.pointer);
}
extern "C" CRef func_001254B8(int unused_count, CRef *arguments, void *unused_frame)
{
    union { qword q; float f[4]; } vel;
    qword cur = *(qword *)arguments[0].payload.pointer;
    qword target = *(qword *)arguments[1].payload.pointer;
    qword pos = func_00120C80(cur, target, func_0012BAE8(&arguments[2]).payload.real, arguments[3].payload.pointer, &vel.q);
    return Pair(pos, &vel.q);
}
