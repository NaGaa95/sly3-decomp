// SLY3_CFLAGS: -Os -G0
struct QueueEntry { int first; int second; int mapped; int fourth; int fifth; };
struct Queue { unsigned char prefix[0x50]; int locked; unsigned char gap54[0x98 - 0x54]; int count; struct QueueEntry *entries; };
int func_00185980(int index);
void func_00186000(struct Queue *self, int first, int index, int second, int fourth, int fifth)
{
    if(!self->locked) {
        int n = self->count;
        if(n < 32) {
            struct QueueEntry *entry = self->entries + n;
            self->count = n + 1;
            entry->first = first;
            entry->second = second;
            entry->mapped = func_00185980(index);
            entry->fourth = fourth;
            entry->fifth = fifth;
        }
    }
}
