// SLY3_CFLAGS: -Os -G0
typedef int Quad __attribute__((mode(TI)));
struct CollectRequest { int bytes; int alignment; };
struct CollectNode { unsigned short first; unsigned short second; unsigned char gap4[4]; struct CollectNode *next; };
struct CollectSource { unsigned char prefix[0x10]; struct CollectNode *nodes; };
struct CollectRecord { unsigned char gap0[8]; struct CollectSource *source; };
struct CollectQuery { unsigned char prefix[4]; int count; unsigned char gap8[4]; void *handle; };
struct CollectList { unsigned char prefix[4]; unsigned char *quads; };
void *func_001D2770(void *receiver);
void func_001D2798(void *receiver, int flags);
void *func_001D25B0(struct CollectRequest *request);
int func_00119C20(void *handle, int limit, Quad quad, int *capacity, struct CollectRecord **records, float scale);
int func_0018B330(struct CollectList *list, struct CollectQuery *query, int key, int limit, struct CollectNode **out)
{
    unsigned char frame[16];
    struct CollectRequest request;
    struct CollectRequest *pointer;
    int capacity;
    struct CollectRecord *records;
    struct CollectRecord *start;
    int found, total, i, entries;
    func_001D2770(frame);
    entries = 0x1555;
    if(query->count <= 0x1554) entries = query->count;
    capacity = entries;
    pointer = &request;
    request.bytes = entries * 12;
    pointer->alignment = 0x10;
    start = func_001D25B0(pointer);
    records = start;
    if(func_00119C20(query->handle, 0x7FFFFFFF, *(Quad *)(list->quads + key * 16), &capacity, &records, 1.0f) != 2) {
        func_001D2798(frame, 2);
        return 0;
    }
    total = records - start;
    found = 0;
    for(i = 0; i < total; i++) {
        struct CollectNode *node;
        for(node = start[i].source->nodes; node; node = node->next) {
            int j;
            if(key != node->first && key != node->second) continue;
            for(j = 0; j < found; j++) if(node == out[j]) break;
            if(j < found) continue;
            if(found < limit) out[found++] = node;
        }
    }
    func_001D2798(frame, 2);
    return found;
}
