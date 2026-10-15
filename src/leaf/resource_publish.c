// SLY3_CFLAGS: -Os -G0

typedef unsigned long ResourceWord64;
struct ResourceBytes4 { unsigned char bytes[4]; };
struct ResourcePublishLink { unsigned char opaque[6]; unsigned char count; };
struct ResourcePublishSource {
    int id;
    unsigned char kind,flags,metadata,opaque7;
    struct ResourceBytes4 color;
    unsigned char opaqueC[12];
    struct ResourcePublishLink *link;
    unsigned char opaque1C[16];
};
struct ResourcePublished28 {
    int id;
    unsigned short metadata,flags;
    struct ResourceBytes4 color;
    int count;
    ResourceWord64 *words;
    void *heap;
    struct ResourcePublished28 *next;
};
struct ResourcePublishList { void *head,*tail; int next_offset; };
extern struct ResourcePublishList D_00479D98;
void *func_00117B40(void *heap,unsigned int bytes,int category);
ResourceWord64 func_00233CD0(struct ResourcePublishLink *link,int index,int selector);
void func_0011AD80(struct ResourcePublishList *list,void *node);
typedef char ResourceWordSize8[(sizeof(ResourceWord64)==8)?1:-1];
typedef char ResourceSourceSize44[(sizeof(struct ResourcePublishSource)==44)?1:-1];
typedef char ResourcePublishedSize28[(sizeof(struct ResourcePublished28)==28)?1:-1];
typedef char ResourceColorAlign1[(__alignof__(struct ResourceBytes4)==1)?1:-1];

void func_00234DA8(struct ResourcePublishSource *source,void *heap)
{
    int i=0;
    struct ResourcePublishLink *link;
    struct ResourcePublished28 *published=func_00117B40(heap,28,0x2B);
    published->id=source->id;
    published->metadata=source->metadata;
    published->flags=source->flags;
    published->color=source->color;
    link=source->link;
    published->count=link->count;
    published->words=func_00117B40(heap,published->count*8,0x2F);
    published->heap=heap;
    for(;i<published->count;i++) {
        ResourceWord64 *word=(ResourceWord64 *)((i<<3)+(unsigned int)published->words);
        *word=func_00233CD0(link,i,0);
    }
    func_0011AD80(&D_00479D98,published);
}
