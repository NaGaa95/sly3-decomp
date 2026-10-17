// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct Node;
struct PairPtr;
class CRef;
extern "C" {
Node *func_002BA6B8();
void func_0012B1D8(CRef *, Node *);
void func_002BA760(PairPtr *, Node *);
void func_002BA780(PairPtr *, Node *);
void func_002BA840(Node *, int);
void *func_00292034(void *, int, unsigned int);
}
class CRef {
public:
    short tag, references;
    union { int integer; float real; void *pointer; Node *pair; } payload;
    CRef() { tag = -1; }
    CRef(int kind) { InitTag(kind); }
    CRef(Node *node) { func_0012B1D8(this, node); }
    CRef(const CRef &);
    CRef &operator=(const CRef &);
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
struct ArgumentRecord { int specification; int mode; int rest[8]; };
extern "C" CRef func_00249D98(void *address, ArgumentRecord *record);
extern "C" CRef func_0024AD90(int count, const int *specifications, void *const *argumentAddresses)
{
    if (!count) return CRef(0);
    ArgumentRecord record;
    PairPtr head;
    func_00292034(&record, 0, sizeof record);
    record.mode = 2;
    PairPtr *slot = &head;
    for (int i = 0; i < count; i++) {
        void *address = argumentAddresses[i];
        record.specification = specifications[i];
        PairPtr node(func_002BA6B8());
        node->CRef::operator=(func_00249D98(address, &record));
        *slot = node.p;
        slot = &node->next;
    }
    return CRef(head.p);
}
