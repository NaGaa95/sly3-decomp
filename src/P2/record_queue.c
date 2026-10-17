// SLY3_CFLAGS: -Os -G0
struct Reference { unsigned char bytes[8]; };
struct QueuedObject { unsigned char prefix[0x24]; struct Reference reference; };
struct QueueEntry { struct QueuedObject *owner; struct Reference reference; };
struct EntryQueue { unsigned char prefix[0x54]; struct QueueEntry *cursor; struct QueueEntry *end; };
extern struct EntryQueue *D_0036C328;
void func_002371C8(struct QueuedObject *object,struct Reference *reference);
void func_00237168(struct QueuedObject *object)
{
    struct EntryQueue *queue=D_0036C328;
    if(queue) {
        struct QueueEntry *entry=queue->cursor;
        if(entry<queue->end) {
            queue->cursor=entry+1;
            entry->owner=object;
            entry->reference=object->reference;
        }
    } else
        func_002371C8(object,&object->reference);
}
