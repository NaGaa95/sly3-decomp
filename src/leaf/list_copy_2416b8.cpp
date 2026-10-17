// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct Node;
struct PairPtr;
class CRef;
extern "C" {
Node *func_002BA6B8();
CRef *func_0012B768(CRef *, void *);
void func_0012B1D8(CRef *, Node *);
void func_002BA760(PairPtr *, Node *);
void func_002BA780(PairPtr *, Node *);
void func_002BA840(Node *, int);
void func_002BE8D0(void *, int);
}
class CRef {
public:
    short tag, references;
    union { int integer; float real; void *pointer; Node *pair; } payload;
    CRef() { tag = -1; }
    CRef(int kind) { InitTag(kind); }
    CRef(Node *node) { func_0012B1D8(this, node); }
    CRef &operator=(void *object) { return *func_0012B768(this, object); }
    void InitTag(int);
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
struct ListScope {
    ~ListScope() { func_002BE8D0(this, 2); }
};
struct ListEntry { unsigned char prefix[0x24]; ListEntry *next; };
struct ListSource { unsigned char prefix[0x54]; ListEntry *first; };
extern "C" CRef func_002416B8(ListSource *source)
{
    ListScope scope;
    PairPtr head;
    head = (Node *)0;
    PairPtr *slot = &head;
    for (ListEntry *entry = source->first; entry; entry = entry->next) {
        PairPtr node(func_002BA6B8());
        node->CRef::operator=((void *)entry);
        *slot = node.p;
        slot = &node->next;
    }
    if (head.p) return CRef(head.p);
    return CRef(0);
}
