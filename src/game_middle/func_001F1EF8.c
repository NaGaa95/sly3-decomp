// Copy the live entries' leading words of a queue snapshot into a small buffer and pack them into the output.
// SLY3_CFLAGS: -O2 -G0 -ffast-math -fno-schedule-insns
struct SnapshotEntry { int word; int pad[3]; };
struct SnapshotQueue {
    char pad[0x414];
    struct SnapshotEntry entries[8];
    int tail;
    int head;
};
void func_0024AEF8(void *output, int count, int type, int *values);
void *func_001F1EF8(void *output, struct SnapshotQueue *queue)
{
    int words[8];
    int count = 0;
    int i;
    int head = queue->head;
    int tail = queue->tail;
    for (i = head; i < tail; i++)
        words[count++] = queue->entries[i].word;
    func_0024AEF8(output, count, 6, words);
    return output;
}
