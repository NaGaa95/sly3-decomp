// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CFrame;
class CRef {
public:
    short tag, word2;
    union { int word; float real; void *pointer; } payload;
    CRef(const CRef &);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &);
};
struct Node {
    CRef value;
    unsigned int tracked_links;
    Node *next;
};
typedef char CRef8[(sizeof(CRef) == 8) ? 1 : -1];
typedef char Node16[(sizeof(Node) == 16) ? 1 : -1];
extern "C" CRef func_001257E8(int count, CRef *arguments, CFrame *frame)
{
    CRef result(arguments[0]);
    if (arguments[1].tag)
        arguments = (CRef *)arguments[1].payload.pointer;
    else
        arguments = 0;
    // The list stores each value in its CRef prefix.
    for (; arguments; arguments = (CRef *)((Node *)arguments)->next) {
        CRef *value = arguments;
        if (result.tag == 0x13) {
            if (value->tag == 0x13) {
                if (value->payload.word < result.payload.word)
                    result = *value;
            } else if ((float)result.payload.word > value->payload.real) {
                result = *value;
            }
        } else {
            if (value->tag == 0x13) {
                if (result.payload.real > (float)value->payload.word)
                    result = *value;
            } else if (value->payload.real < result.payload.real) {
                result = *value;
            }
        }
    }
    return result;
}
