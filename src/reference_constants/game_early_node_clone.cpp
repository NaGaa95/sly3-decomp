// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Clone a retained list through the original tagged-reference clone API.
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
extern "C" CRef func_0012B928(CRef *source, void *parentOverride, void *forwardedContext);
extern "C" PairPtr func_0012AA50(Node *source, void *parentOverride, void *forwardedContext)
{
    PairPtr clone(func_002BA6B8());
    clone->CRef::operator=(func_0012B928(source, parentOverride, forwardedContext));
    if (source->next.p) {
        clone->next = func_0012AA50(source->next.p, parentOverride, forwardedContext).p;
    }
    return PairPtr(clone.p);
}
