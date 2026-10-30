// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// func_00125388: script builtin: GSmooth (func_0011E598) on three float arguments and an SMP, returning the list
// (new value, new rate). CRef/Node modelling follows src/engine/vector_pair.cpp.
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
};
struct Node;
extern "C" {
Node *func_002BA6B8();
void func_002BA760(Node **slot, Node *node);
void func_002BA780(Node **slot, Node *node);
void func_002BA840(Node *node, int flags);
CRef func_0012BAE8(CRef *reference);
float func_0011E598(float gCur, float gTarget, float dt, void *psmp, float *pdgNext);
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
static inline CRef Pair(float a, float *pb)
{
    NodeRef result;
    result.Set(func_002BA6B8());
    result->reference = a;
    result->SetNext(func_002BA6B8());
    result->next->reference = *pb;
    return CRef(result.pointer);
}
extern "C" CRef func_00125388(int unused_count, CRef *arguments, void *unused_frame)
{
    float g, dg;
    {
        CRef cur = func_0012BAE8(&arguments[0]);
        float gCur = cur.payload.real;
        CRef target = func_0012BAE8(&arguments[1]);
        float gTarget = target.payload.real;
        CRef dt = func_0012BAE8(&arguments[2]);
        g = func_0011E598(gCur, gTarget, dt.payload.real, arguments[3].payload.pointer, &dg);
    }
    return Pair(g, &dg);
}
