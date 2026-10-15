// Reference: Sly 2 func_001EC880; measured Sly 3 linked prefix and cleanup.
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct ResourceLookupNode {
    int id;
    char reserved4[0x18 - 4];
    ResourceLookupNode *next;
};
extern "C" void *D_00479D98;
class ResourceSearchToken {
public:
    ~ResourceSearchToken();
};

extern "C" void *func_00235EC8(int id)
{
    if (id == -1)
        return 0;
    ResourceSearchToken token;
    for (ResourceLookupNode *node = (ResourceLookupNode *)D_00479D98;
         node; node = node->next) {
        if (node->id == id)
            return node;
    }
    return 0;
}
