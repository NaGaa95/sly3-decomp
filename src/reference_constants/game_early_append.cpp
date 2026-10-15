// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Append variadic list values, cloning each non-final outer argument.
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
    short tag, references; // Word 2 is live only in a Node, not a scalar reference.
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
extern "C" PairPtr func_0012AA50(Node *head, void *parentContext, void *forwardedContext);
extern "C" CRef func_00122EB0(int count, CRef *arguments, EvalFrame *frame)
{
    if (arguments[0].tag == 0) return arguments[0];
    Node *argument = arguments[0].payload.pair;
    PairPtr outputRoot;
    Node *last;
    while (argument) {
        if (argument->tag == 0x1D) {
            PairPtr list;
            if (argument->next.p) {
                list = func_0012AA50(argument->payload.pair, 0, 0).p;
            } else {
                list = argument->payload.pair;
            }
            if (!outputRoot.p) {
                outputRoot = func_002BA6B8();
                outputRoot->CRef::operator=(list.p);
            } else {
                last->next = list.p;
            }
            last = list;
            while (last->next.p) last = last->next.p;
        }
        argument = argument->next.p;
    }
    if (!outputRoot.p) return CRef(0);
    return CRef(outputRoot->payload.pair);
}
