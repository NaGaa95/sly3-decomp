// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef unsigned int uint;
struct SO;
typedef struct VE { short delta, pad; void (*fn)(struct SO *, void *, void *); } VE;
typedef struct SO { char pad[0xC]; VE *vt; char pad10[0x10]; uint flags; char position[0x14]; char list[0x10]; int vectorCount; void *vectors; } SO;
typedef struct D { signed char channel, segments; int flags : 8; char kind; char pad4[4]; void *chain; char padC[4]; int words; } D;
typedef struct E { int value; void *transform; void *parent; uint pad : 14, first : 10, count : 8; char *data; uint base; char *segments; int word1C; SO *object; void *sphere; } E;
typedef struct P { SO *owner; char pad4[0x20]; int objectCount; SO **objects; char pad2C[12]; int count; D *descriptors; E *entries; char pad44[0x14]; int word58; } P;
typedef struct LINK { int pad0; void *bounds; int pad8; SO *object; int next; } LINK;
typedef struct REQUEST { int bytes, alignment; } REQUEST;
extern int D_0046FF40;
extern LINK D_0046FF48[];
void *func_001D24D0(REQUEST *, void *);
SO *func_00236F58(SO *);
void func_0018FBB0(D *, E *, int, void *, int, void *, void *);
void CopyAb(void *, const void *, uint);
void func_0011AD68(int *);
void func_0011ADA8(void *, LINK *);
void func_00235D78(int, int, int, void *, void *);

static inline void *Copy(int bytes, void *source)
{
    REQUEST request;
    request.bytes = bytes;
    request.alignment = 16;
    return func_001D24D0(&request, source);
}
static inline void ReadTransform(SO *object, void *stream, void *output)
{
    VE *method = &object->vt[56];
    method->fn((SO *)((char *)object + method->delta), stream, output);
}

static inline void CopyObjects(P *p)
{
    int i;
    for (i = 0; i < p->objectCount; i++) {
        if (p->objects[i]->flags & 4) {
            p->objects = (SO **)Copy(p->objectCount * 4, p->objects);
            return;
        }
    }
}

void func_00194B20(P *p, SO *owner, void *stream)
{
    int i;
    p->owner = owner;
    p->entries = (E *)Copy(p->count * sizeof(E), p->entries);
    p->word58 = 0;
    CopyObjects(p);
    for (i = 0; i < p->count; i++) {
        D *descriptor = &p->descriptors[i];
        E *entry = &p->entries[i];
        int j;
        int cloned;
        int count;
        void *old;
        void *data;
        ReadTransform(owner, stream, &entry->transform);
        entry->segments = (char *)Copy(descriptor->segments * 0x50, entry->segments);
        for (j = 0; j < descriptor->segments; j++) {
            uint address = (uint)entry->segments;
            address += j * 0x50;
            ReadTransform(owner, stream, (void *)(address + 0xC));
        }
        cloned = entry->object && (entry->object->flags & 4);
        if (cloned) {
            int k;
            SO *object = func_00236F58(entry->object);
            for (k = 0; k < p->objectCount; k++) {
                if (p->objects[k] == entry->object) {
                    p->objects[k] = object;
                    break;
                }
            }
            entry->object = object;
        }
        if (!descriptor->chain && !cloned)
            continue;
        count = 0;
        old = 0;
        data = 0;
        if (descriptor->flags & 3) {
            count = descriptor->words;
            old = entry->data;
            entry->data = Copy(count * 16, old);
            data = entry->data;
        } else {
            if (entry->object) {
                data = entry->object->vectors;
                count = entry->object->vectorCount;
                old = data;
                if (cloned) {
                    entry->object->vectors = Copy(count * 16, data);
                    data = entry->object->vectors;
                }
            }
            func_0018FBB0(descriptor, entry, descriptor->words, entry->data, count, data, old);
        }
        if (entry->object) {
            int n = entry->count;
            if (D_0046FF40 + n <= 0x400) {
                int m, end, first;
                CopyAb(&D_0046FF48[D_0046FF40], &D_0046FF48[entry->first], n * sizeof(LINK));
                entry->first = D_0046FF40;
                D_0046FF40 += n;
                first = entry->first;
                end = first + entry->count;
                for (m = first; m < end; m++) {
                    LINK *link = &D_0046FF48[m];
                    if (cloned) {
                        link->bounds = &entry->object->position;
                        link->object = entry->object;
                    }
                    func_0011AD68(&link->next);
                    func_0011ADA8(link->object->list, link);
                }
                func_00235D78(entry->first, entry->count, count * 16, old, data);
            }
        }
    }
}
