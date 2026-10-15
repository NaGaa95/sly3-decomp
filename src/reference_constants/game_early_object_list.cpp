// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Node;
struct Basic;
struct PairPtr;
class CRef;
extern "C" {
    Node *func_002BA6B8();
    CRef *func_0012B6C8(CRef *, Node *);
    CRef *func_0012B768(CRef *, Basic *);
    void func_002BA780(PairPtr *, Node *);
}
class CRef {
public:
    short tag, word2;
    union { int word; float real; void *pointer; Node *node; } payload;
    CRef() { tag = -1; }
    CRef(int kind) { InitTag(kind); }
    CRef(const CRef &);
    void InitTag(int kind);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(Node *node) { return *func_0012B6C8(this, node); }
    CRef &operator=(Basic *object) { return *func_0012B768(this, object); }
};
struct PairPtr {
    Node *p;
    PairPtr() { p = 0; }
    void operator=(Node *node) { func_002BA780(this, node); }
};
struct Node : CRef {
    unsigned int tracking_word;
    PairPtr next;
};
typedef char CRef8[(sizeof(CRef) == 8) ? 1 : -1];
typedef char Node16[(sizeof(Node) == 16) ? 1 : -1];
typedef char BasicPointer4[(sizeof(Basic *) == 4) ? 1 : -1];
extern "C" CRef func_00126060(int count, Basic **objects)
{
    if (count == 0) return CRef(0);
    CRef result;
    Node *previous = 0;
    for (int i = 0; i < count; ++i) {
        Node *node = func_002BA6B8();
        if (previous)
            previous->next = node;
        else
            result = node;
        node->CRef::operator=(objects[i]);
        previous = node;
    }
    return result;
}
