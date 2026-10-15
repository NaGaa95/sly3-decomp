// SLY3_CFLAGS: -Os -G0
struct CleanupList { void *head, *tail; int linkOffset; };
struct CleanupIterator { struct CleanupList *list; void **next; int linkOffset; struct CleanupIterator *previous; };
struct CleanupEventEntry { short delta, reserved; void (*call)(void *,int,void *,int,void *,void *); };
struct CleanupObject {
    char prefix[0xC]; struct CleanupEventEntry *table;
    char pad10[0x3C-0x10]; int storage;
    char pad40[8]; struct CleanupList children;
    char pad54[4]; void *selected; float elapsed; unsigned long flags;
};
extern struct CleanupIterator *D_0036AE94;
extern void func_0022B930(void *);
extern void func_002263B0(void *,float);
extern void func_002262B0(void *);
extern void func_001C9118(void *,int);
typedef char CheckList12[sizeof(struct CleanupList)==12?1:-1];
typedef char CheckIterator16[sizeof(struct CleanupIterator)==16?1:-1];
typedef char CheckPrefix68[sizeof(struct CleanupObject)==0x68?1:-1];
static inline void InitializeCleanupIterator(struct CleanupIterator *iterator,struct CleanupList *list) {
    iterator->list=list;
    iterator->next=(void **)list;
    iterator->linkOffset=list->linkOffset;
    iterator->previous=D_0036AE94;
    D_0036AE94=iterator;
}
static inline void *NextCleanupItem(struct CleanupIterator *iterator) {
    void *item=*iterator->next;
    iterator->next=(void **)((unsigned int)item+iterator->linkOffset);
    return item;
}
void func_00226050(void *receiver) {
    struct CleanupObject *object=(struct CleanupObject *)receiver;
    struct CleanupIterator iterator;
    void *item;
    if (!(object->flags&1L)) return;
    object->selected=0;
    object->elapsed=0.0f;
    object->flags&=~1L;
    InitializeCleanupIterator(&iterator,&object->children);
    while ((item=NextCleanupItem(&iterator))!=0) func_0022B930(item);
    func_002263B0(object,1.0f);
    func_002262B0(object);
    if (object->flags&2L) {
        func_001C9118(object,2);
        if ((object->storage^1)&1) *(int *)object->storage&=~2;
        else object->storage&=~2;
    }
    object->table[3].call((char *)object+object->table[3].delta,6,0,0,0,0);
    D_0036AE94=iterator.previous;
}
