// Copy each original eight-byte reference into every linked destination, then finish the real automatic cleanup scope.
// Complete original body, actual inputs and every initialized section are independently reviewed.
// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct Reference {
    unsigned char bytes[8];
};
struct Node {
    char prefix[8];
    Reference *destination;
    char middle[4];
    const Node *next;
};
struct Receiver {
    char prefix[0x38];
    const Node *head;
};
extern "C" void func_001D2898(void *destination, const void *source, unsigned int bytes);
extern "C" void func_002BF1F0(void *object, int flags);
class CopyScope {
    public: CopyScope() {
    }
    ~CopyScope() {
        func_002BF1F0(this, 2);
    }
};
extern "C" void func_002371C8(const Receiver *p, const Reference *source) {
    CopyScope scope;
    for (const Node *node = p->head; node; node = node->next) func_001D2898(node->destination, source, 8);
}
