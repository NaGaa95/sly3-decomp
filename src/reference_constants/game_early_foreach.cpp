// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Invoke a callable for each list element through the original evaluator.
struct Node;
struct PairPtr;
struct EvalFrame;
class CRef;
extern "C" {
Node *func_002BA6B8();
CRef *func_0012B6C8(CRef *, Node *);
void func_0012B1D8(CRef *, Node *);
void func_002BA760(PairPtr *, Node *);
void func_002BA780(PairPtr *, Node *);
void func_002BA840(Node *, int);
}
class CRef {
public:
    short tag, references; // Word2 is live only in a Node, not a scalar reference.
    union { int integer; float real; void *pointer; Node *pair; } payload;
    CRef() { tag = -1; }
    CRef(int kind) { InitTag(kind); }
    CRef(Node *node) { func_0012B1D8(this, node); }
    CRef(const CRef &);
    CRef &operator=(const CRef &);
    CRef &operator=(Node *node) { return *func_0012B6C8(this, node); }
    void InitTag(int);
    void Decref();
    ~CRef() { Decref(); }
};
struct PairPtr {
    Node *p;
    PairPtr() { p = 0; }
    PairPtr(const PairPtr &);
    PairPtr(Node *node) { func_002BA760(this, node); }
    void operator=(Node *node) { func_002BA780(this, node); }
    Node *operator->() { return p; }
    operator Node *() { return p; }
    ~PairPtr();
};
struct Node : CRef {
    unsigned int trackedLinks;
    PairPtr next;
};
inline PairPtr::~PairPtr()
{
    Node *node = p;
    if (node && --node->references == 0) func_002BA840(node, 3);
}
typedef char CheckCRef8[(sizeof(CRef)==8)?1:-1];
typedef char CheckPairPtr4[(sizeof(PairPtr)==4)?1:-1];
typedef char CheckNode16[(sizeof(Node)==16)?1:-1];
extern "C" PairPtr func_001230A0(CRef **callableSlot, CRef **argumentSlot);
extern "C" CRef func_001296F0(Node *expression, EvalFrame *frame);
extern "C" CRef func_001235C8(int count, CRef *arguments, EvalFrame *frame)
{
    if (arguments[1].tag == 0x1D) {
        CRef *callableSlot, *argumentSlot;
        PairPtr callTemplate = func_001230A0(&callableSlot, &argumentSlot);
        *callableSlot = arguments[0];
        Node *node = arguments[1].payload.pair;
        while (node) {
            *argumentSlot = *node;
            CRef value = func_001296F0(callTemplate.p, frame);
            node = node->next.p;
        }
    }
    return CRef(0x22);
}
