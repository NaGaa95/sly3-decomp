// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Node;
struct PairPtr;
struct Frame;
struct Basic;
struct ObjectContext { char prefix[0x38]; void *scope; };
struct Game { char prefix[0x4634]; void *default_scope; };
class CRef;
extern "C" {
    Node *func_002BA6B8();
    CRef *func_0012B6C8(CRef *, Node *);
    CRef *func_0012B1D8(CRef *, Node *);
    CRef *func_0012B768(CRef *, Basic *);
    void func_002BA760(PairPtr *, Node *);
    void func_002BA780(PairPtr *, Node *);
    void func_002BA840(Node *, int);
}
class CRef {
public:
    short tag;
    short word2;
    union { int word; float real; void *pointer; Node *node; ObjectContext *object; } payload;
    CRef() { tag = -1; }
    CRef(Node *node);
    CRef(const CRef &);
    CRef &operator=(const CRef &);
    CRef &operator=(Node *node) { return *func_0012B6C8(this, node); }
    CRef &operator=(Basic *object) { return *func_0012B768(this, object); }
    void Decref();
    ~CRef() { Decref(); }
};
struct PairPtr {
    Node *p;
    PairPtr(Node *node) { func_002BA760(this, node); }
    PairPtr(const PairPtr &);
    void operator=(Node *node) { func_002BA780(this, node); }
    Node *operator->() { return p; }
    operator Node *() { return p; }
    ~PairPtr();
};
struct Node : CRef { unsigned int tracking_word; PairPtr next; };
inline PairPtr::~PairPtr()
{
    Node *node = p;
    // Only Node word2 is a live16-bit counter; scalar reference word2 stays opaque.
    if (node && --node->word2 == 0) func_002BA840(node, 3);
}
typedef char CRef8[(sizeof(CRef) == 8) ? 1 : -1];
typedef char PairPtr4[(sizeof(PairPtr) == 4) ? 1 : -1];
typedef char Node16[(sizeof(Node) == 16) ? 1 : -1];
extern Game D_00475480;
extern "C" Basic *func_0017E1D8(Game *, int flags, int key,
                                ObjectContext *owner, void *scope);
extern "C" CRef func_001262A0(int count, CRef *arguments, Frame *frame)
{
    CRef result;
    if (arguments[0].tag == 0) return arguments[0];
    ObjectContext *owner = arguments[1].payload.object;
    ObjectContext *scope_object;
    if (arguments[2].tag)
        scope_object = arguments[2].payload.node->payload.object;
    else
        scope_object = owner;
    PairPtr output_root(func_002BA6B8());
    Node *node = arguments[0].payload.node;
    Node *previous;
    while (node) {
        PairPtr copy(func_002BA6B8());
        Game *game = &D_00475480;
        CRef *destination = copy.p;
        int key = node->payload.word;
        destination->operator=(func_0017E1D8(game, owner ? 1 : 5,
            key, owner, scope_object ? scope_object->scope : game->default_scope));
        if (output_root->tag != 0x1D)
            output_root->CRef::operator=(copy.p);
        else
            previous->next = copy.p;
        node = node->next.p;
        previous = copy;
    }
    result = CRef(output_root->payload.node);
    return result;
}
