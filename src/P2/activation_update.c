// SLY3_CFLAGS: -Os -G0
struct ActivationUpdateList { void *head, *tail; int linkOffset; };
struct ActivationUpdateIterator {
    struct ActivationUpdateList *list;
    void **next;
    int linkOffset;
    struct ActivationUpdateIterator *previous;
};
struct ActivationUpdateView {
    unsigned char prefix[0x3C];
    int storage;
    unsigned char toList[8];
    struct ActivationUpdateList children;
    unsigned char toElapsed[8];
    float elapsed;
    unsigned long flags;
};
extern struct ActivationUpdateIterator *D_0036AE94;
extern float D_0036BB9C, D_0036BBDC;
void func_001C8168(void *);
void func_002265E0(void *);
int func_0011B0F0(void *);
void func_00226050(void *);
static inline void StartActivationIterator(struct ActivationUpdateIterator *iterator,
                                           struct ActivationUpdateList *list)
{
    iterator->list = list;
    iterator->next = (void **)list;
    iterator->linkOffset = list->linkOffset;
    iterator->previous = D_0036AE94;
    D_0036AE94 = iterator;
}
static inline void *NextActivationItem(struct ActivationUpdateIterator *iterator)
{
    void *item = *iterator->next;
    iterator->next = (void **)((unsigned int)item + iterator->linkOffset);
    return item;
}
void func_00225130(void *receiver)
{
    struct ActivationUpdateView *object = receiver;
    struct ActivationUpdateIterator iterator;
    void *item;
    int flags;
    func_001C8168(receiver);
    if (!(object->flags & 1L))
        return;
    flags = object->storage;
    if ((flags ^ 1) & 1)
        flags = *(int *)flags;
    if (flags & 0x200)
        object->elapsed += D_0036BBDC;
    else
        object->elapsed += D_0036BB9C;
    StartActivationIterator(&iterator, &object->children);
    while ((item = NextActivationItem(&iterator)) != 0)
        func_002265E0(item);
    if (func_0011B0F0(&object->children))
        func_00226050(receiver);
    D_0036AE94 = iterator.previous;
}
