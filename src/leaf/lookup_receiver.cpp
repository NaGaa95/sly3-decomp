// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct LookupNode {
    char reserved0[0x14];
    LookupNode *next;
    char reserved18[0x28 - 0x18];
    void *receiver;
};
struct LookupOwner {
    char reserved0[0x58];
    LookupNode *first;
};
class LookupToken {
public:
    ~LookupToken();
};
extern "C" LookupNode *func_00239A10(LookupOwner *owner, void *receiver)
{
    LookupToken token;
    for (LookupNode *node = owner->first; node; node = node->next) {
        if (node->receiver == receiver)
            return node;
    }
    return 0;
}
