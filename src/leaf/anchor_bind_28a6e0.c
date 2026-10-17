// SLY3_CFLAGS: -Os -G0
struct CopyRequest { int size,kind; };
struct Node { unsigned char prefix[0xA4]; struct Node *next; };
struct Manager {
    unsigned char prefix[0x470];
    unsigned char firstDefault[0x100],secondDefault[0x100];
    void *first,*second;
    struct Node *nodes;
    unsigned char gap67C[0xC];
    void *anchor;
};
void *func_001D24D0(struct CopyRequest *request,void *source);
void func_002896D0(struct Manager *manager,struct Node *node);
void func_0028A6E0(struct Manager *manager,void *anchor)
{
    struct Node *node;
    manager->anchor=anchor;
    if(anchor) {
        if(!manager->first) {
            struct CopyRequest request;
            request.size=0x100;
            request.kind=0x10;
            manager->first=func_001D24D0(&request,manager->firstDefault);
            request.size=0x100;
            request.kind=0x10;
            manager->second=func_001D24D0(&request,manager->secondDefault);
        }
    }
    for(node=manager->nodes;node;node=node->next)
        func_002896D0(manager,node);
}
