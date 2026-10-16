// SLY3_CFLAGS: -Os -G0
struct EngineFlushList { void *first,*last;int offset; };
struct EngineFlushIterator { struct EngineFlushList *list;void **cursor;int offset;struct EngineFlushIterator *previous; };
struct EngineFlushObjectEntry { short delta,padding;void (*call)(void *); };
struct EngineFlushObject { unsigned char prefix[0xC];struct EngineFlushObjectEntry *table; };
struct EngineFlushHandle { struct EngineFlushObject *object; };
struct EngineFlushGame { unsigned char prefix[0x3DE8];struct EngineFlushList handles;unsigned int unused3DF4;struct EngineFlushList pending; };
extern struct EngineFlushIterator *D_0036AE94;
void func_0015AF48(void *);
int func_0011B0C0(void *,void *);
void func_0011B028(void *,void *);
static __inline__ void BeginEngineFlush(struct EngineFlushIterator *iterator,struct EngineFlushList *list) {
    iterator->list=list;
    iterator->cursor=(void **)list;
    iterator->offset=list->offset;
    iterator->previous=D_0036AE94;
    D_0036AE94=iterator;
}
static __inline__ void *NextEngineFlush(struct EngineFlushIterator *iterator) {
    void *node=*iterator->cursor;
    iterator->cursor=(void **)((unsigned int)node+(unsigned int)iterator->offset);
    return node;
}
void func_0015AE70(struct EngineFlushGame *game) {
    struct EngineFlushIterator iterator;
    struct EngineFlushHandle *handle;
    func_0015AF48(game);
    BeginEngineFlush(&iterator,&game->handles);
    while((handle=(struct EngineFlushHandle *)NextEngineFlush(&iterator))!=0) {
        if(func_0011B0C0(&game->pending,handle)) {
            struct EngineFlushObject *object=handle->object;
            struct EngineFlushObjectEntry *entry=&object->table[24];
            entry->call((char *)object+entry->delta);
            func_0011B028(&game->pending,handle);
        }
    }
    D_0036AE94=iterator.previous;
}
