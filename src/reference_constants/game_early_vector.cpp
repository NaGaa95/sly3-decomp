// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CFrame;
class CRef {
public:
    short tag, references;
    union { int word; float real; void *pointer; } payload;
    CRef() { tag = -1; }
    CRef(int kind) { InitTag(kind); }
    CRef(const CRef &);
    void Decref();
    void InitTag(int kind);
    ~CRef() { Decref(); }
};
struct Node {
    CRef value;
    unsigned int tracked_links;
    Node *next;
};
// The original buffer has four float words; only xyz are written here.
// Its reference counter is a separate32-bit word after this16-byte view.
struct VectorStorage { float component[4]; };
typedef char CRef8[(sizeof(CRef) == 8) ? 1 : -1];
typedef char Node16[(sizeof(Node) == 16) ? 1 : -1];
typedef char Vector16[(sizeof(VectorStorage) == 16) ? 1 : -1];
extern "C" CRef func_0012BAE8(CRef *value);
extern "C" CRef func_00123B78(int count, CRef *arguments, CFrame *frame)
{
    CRef result(0x18);
    VectorStorage *vector = (VectorStorage *)result.payload.pointer;
    Node *node;
    if (count > 0)
        node = (Node *)arguments[0].payload.pointer;
    switch (count) {
    case 0:
        vector->component[2] = 0.0f;
        vector->component[1] = 0.0f;
        vector->component[0] = 0.0f;
        break;
    case 1: {
        CRef value = func_0012BAE8(&node->value);
        float component = value.payload.real;
        vector->component[2] = component;
        vector->component[1] = component;
        vector->component[0] = component;
        break;
    }
    case 3: {
        float *component = &vector->component[0];
        for (int i = 0; i < 3; ++i) {
            CRef value = func_0012BAE8(&node->value);
            *component = value.payload.real;
            ++component;
            node = node->next;
        }
        break;
    }
    }
    return result;
}
