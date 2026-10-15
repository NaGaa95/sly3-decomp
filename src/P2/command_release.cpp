// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Finish the selected command chain, clear owned resources, and release the node.
// The temporary retain keeps the receiver alive through both list lifetimes.
// These are consumed prefix views of the original 0x180-byte pool allocation.
struct CommandReleaseVirtualEntry {
    short delta;
    short reserved;
    void (*call)(void *);
};
struct CommandReleaseList {
    void *head;
    void *tail;
    int link_offset;
};
struct CommandReleaseIterator;
extern CommandReleaseIterator *D_0036AE94;
struct CommandReleaseIterator {
    CommandReleaseList *list;
    void **cursor;
    int link_offset;
    CommandReleaseIterator *previous;
    CommandReleaseIterator(CommandReleaseList *l)
        : list(l), cursor((void **)l), link_offset(l->link_offset), previous(D_0036AE94)
    {
        D_0036AE94 = this;
    }
    ~CommandReleaseIterator() {
        D_0036AE94 = previous;
    }
    void *Next() {
        void *node = *cursor;
        cursor = (void **)((char *)node + link_offset);
        return node;
    }
};
struct CommandReleaseCommand { unsigned char bytes[16]; };
struct CommandReleaseRecord { char prefix[8]; unsigned int options; };
struct CommandReleaseOwnerView { char prefix[0x44]; CommandReleaseCommand *commands; CommandReleaseList nodes; };
struct CommandReleaseNodeView {
    char prefix[0xC]; CommandReleaseVirtualEntry *table; int reference_count; CommandReleaseOwnerView *owner;
    void *retained18; void *word1C; char gap20[0xC]; CommandReleaseRecord *record;
    int executing; CommandReleaseCommand *command;
    char gap38[0x114-0x38]; void *resource; int word118;
    char gap11C[0x15C-0x11C]; CommandReleaseList allocated_nodes;
};
class CommandReleaseRetainScope {
    CommandReleaseNodeView *receiver;
public:
    CommandReleaseRetainScope(CommandReleaseNodeView *p) : receiver(p) {
        p->table[1].call((char *)p + p->table[1].delta);
    }
    ~CommandReleaseRetainScope() {
        receiver->table[2].call((char *)receiver + receiver->table[2].delta);
    }
};
extern "C" {
    extern char D_00479D5C[];
    int func_0022BB50(CommandReleaseNodeView *);
    void func_0011B028(CommandReleaseList *,void *);
    void func_0011E1F0(void *,void *);
    void func_00226D00(CommandReleaseNodeView *);
    void func_002BF050(void **,void *);
    void func_0022B678(CommandReleaseNodeView *); void func_0022B6E0(CommandReleaseNodeView *);
    void func_0022B718(CommandReleaseNodeView *); void func_0022B770(CommandReleaseNodeView *);
    void func_0022B7B8(CommandReleaseNodeView *); void func_0022B7F0(CommandReleaseNodeView *);
    void func_0022B828(CommandReleaseNodeView *); void func_0022B890(CommandReleaseNodeView *);
    void func_0022B028(CommandReleaseNodeView *,void *,void *); void func_0022B090(CommandReleaseNodeView *,void *);
    void func_0022B238(CommandReleaseNodeView *,int); void func_0022B150(CommandReleaseNodeView *,void *);
    void func_0022B290(CommandReleaseNodeView *,int,unsigned int); void func_00244CA8(void *,float);
    void func_002BBCD8(void **,void *); void func_0022BEE8(CommandReleaseNodeView *);
    void func_0022B930(CommandReleaseNodeView *);
}
void func_0022B930(CommandReleaseNodeView *p)
{
    if (func_0022BB50(p)) return;
    CommandReleaseRetainScope retained(p);
    func_0011B028(&p->owner->nodes,p);
    unsigned int index=p->record->options&0x7FF;
    if (index) {
        CommandReleaseCommand *command=p->owner->commands+index;
        p->executing=1;
        p->command=command;
        p->word118=0;
        while (p->command)
            func_00226D00(p);
        p->executing=0;
    }
    func_002BF050(&p->retained18,0);
    void **resource=&p->resource;
    func_0022B678(p);
    func_0022B6E0(p);
    func_0022B718(p);
    func_0022B770(p);
    func_0022B7B8(p);
    func_0022B7F0(p);
    func_0022B828(p);
    func_0022B890(p);
    func_0022B028(p,0,0);
    func_0022B090(p,0);
    func_0022B238(p,0);
    func_0022B150(p,0);
    func_0022B290(p,0,0);
    if (*resource) {
        func_00244CA8(*resource,0.0f);
        func_002BBCD8(resource,0);
    }
    func_0022BEE8(p);
    CommandReleaseIterator iterator(&p->allocated_nodes);
    void *node;
    while ((node=iterator.Next()) != 0) {
        func_0011B028(&p->allocated_nodes,node);
        func_0011E1F0(D_00479D5C,node);
    }
    p->table[2].call((char *)p+p->table[2].delta);
}
