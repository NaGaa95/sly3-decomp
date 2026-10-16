// SLY3_CFLAGS: -Os -G0
typedef struct ReleaseList { void *first, *last; int linkOffset; } ReleaseList;
typedef struct ReleaseIterator {
    ReleaseList *list;
    void **cursor;
    int linkOffset;
    struct ReleaseIterator *previous;
} ReleaseIterator;
extern ReleaseIterator *D_0036AE94;
extern unsigned char D_0036C658[];
extern unsigned char D_00475480[];
typedef struct ReleaseMethod {
    short adjustment, reserved;
    int (*event)(void *, unsigned int);
} ReleaseMethod;
typedef struct ReleaseObject {
    char prefix[0xC];
    ReleaseMethod *table;
    void *parent;
    char unaccessed[0x438-0x14];
    ReleaseList children;
} ReleaseObject;
void func_001495F8(void *child);
void func_001C7938(void *receiver);
void func_001C7848(int receiverBits);
void *func_0017DBD0(void *game, int group);
void func_0011AE28(void *list, void *object);
void func_001C74B0(void *receiver);
void func_0011AF60(void *list, void *object);

static inline void InitIterator(ReleaseIterator *iterator, ReleaseList *list)
{
    iterator->list=list;
    iterator->cursor=(void **)list;
    iterator->linkOffset=list->linkOffset;
    iterator->previous=D_0036AE94;
    D_0036AE94=iterator;
}
static inline void *Next(ReleaseIterator *iterator)
{
    void *node=*iterator->cursor;
    iterator->cursor=(void **)((unsigned int)node+(unsigned int)iterator->linkOffset);
    return node;
}
void func_001497A0(ReleaseObject *object)
{
    ReleaseIterator iterator;
    void *child;
    InitIterator(&iterator,&object->children);
    while ((child=Next(&iterator))!=0)
        func_001495F8(child);
    func_001C7938(object);
    {
        ReleaseMethod *method=&object->table[30];
        method->event((char *)object+method->adjustment,0);
    }
    func_001C7848((int)object);
    func_0011AE28(func_0017DBD0(D_00475480,0x1A),object);
    if (!object->parent)
        func_001C74B0(object);
    func_0011AF60(D_0036C658,object);
    D_0036AE94=iterator.previous;
}
