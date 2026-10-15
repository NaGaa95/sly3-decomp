// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CFrame;
class CRef {
public:
    short tag, references;
    union { int word; void *pointer; } payload;
    CRef() { tag = -1; }
    CRef(bool value) { tag = 0x15; payload.word = value; }
    CRef(const CRef &);
    CRef &operator=(const CRef &);
    void Decref();
    ~CRef() { Decref(); }
};
struct Node {
    CRef value;
    unsigned int tracked_links;
    Node *next;
};
typedef char CRef8[(sizeof(CRef) == 8) ? 1 : -1];
typedef char Node16[(sizeof(Node) == 16) ? 1 : -1];
extern "C" CRef func_00122458(int count, CRef *arguments, CFrame *frame);
extern "C" CRef func_00122A38(int count, CRef *arguments, CFrame *frame)
{
    CRef comparison;
    CRef inputs[2];
    CRef result(false);
    if (arguments[1].tag == 0x1D) {
        inputs[0] = arguments[0];
        for (Node *node = (Node *)arguments[1].payload.pointer;
             node; node = node->next) {
            inputs[1] = node->value;
            comparison = func_00122458(2, inputs, frame);
            if (comparison.tag == 0x15 && comparison.payload.word) {
                result.payload.word = 1;
                break;
            }
        }
    }
    return result;
}
