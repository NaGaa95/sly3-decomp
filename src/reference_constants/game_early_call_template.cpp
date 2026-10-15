// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Construct a retained call tree with two writable quoted reference slots.
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
    void SetTag(int kind) { Decref(); InitTag(kind); }
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
extern "C" PairPtr func_001230A0(CRef **callableSlot, CRef **argumentSlot)
{
    PairPtr tree(func_002BA6B8());
    tree->CRef::operator=(func_002BA6B8());
    Node *root = tree->payload.pair;
    CRef *firstBranch = root;
    *firstBranch = func_002BA6B8();
    root->next = func_002BA6B8();
    Node *firstQuote = firstBranch->payload.pair;
    firstQuote->SetTag(0x10);
    firstQuote->next = func_002BA6B8();
    *callableSlot = firstQuote->next.p;
    Node *secondBranch = root->next.p;
    secondBranch->CRef::operator=(func_002BA6B8());
    Node *secondQuote = secondBranch->payload.pair;
    secondQuote->SetTag(0x10);
    secondQuote->next = func_002BA6B8();
    *argumentSlot = secondQuote->next.p;
    return PairPtr(tree.p);
}
