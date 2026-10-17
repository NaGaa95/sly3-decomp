// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct SceneRequest { int bytes; int alignment; };
typedef struct SceneEntry { int id; int ref; } SceneEntry;
typedef struct VirtualEntry { short adjustment; short reserved; void (*call)(void *); } VirtualEntry;
typedef struct SceneObject { unsigned char opaque0[12]; VirtualEntry *vtable; unsigned char opaque10[8]; int id; } SceneObject;
typedef struct ObjectList { int opaque0[2]; int count; SceneObject **items; } ObjectList;
typedef struct SceneLink { SceneObject *object; int first; int second; unsigned int mask; int extra; float value; } SceneLink;
typedef struct SceneClass { unsigned int mask; signed char *table; } SceneClass;
typedef struct SceneOwner {
    unsigned char opaque0[0x10];
    void *source;
    unsigned char opaque14[0x40 - 0x14];
    int entryCount;
    SceneEntry *entries;
    int linkCount;
    SceneLink *links;
    int classCount;
    SceneClass *classes;
    unsigned char list58[0x14];
} SceneOwner;
void func_0011AF38(void *list, int size);
void *func_001D2770(void *frame);
void func_001D2798(void *frame, int flags);
void *func_00151A38(void *list);
void func_00151D80(void *source, void *stream, ObjectList *list);
void func_001519C8(void *owner, void *stream);
int func_00118FF8(void *stream);
int func_001191E0(void *stream);
float func_00119260(void *stream);
void *func_001D2470(struct SceneRequest *request);
void *func_001D2670(struct SceneRequest *request);
void *func_001D24D0(struct SceneRequest *request, void *source);
int func_00239AB8(void *owner, int id);
void func_00238FF8(SceneOwner *self, void *stream)
{
    unsigned char frame[16];
    ObjectList list;
    struct SceneRequest request;
    struct SceneRequest *pointer;
    unsigned int classes[32];
    int i, j, k, bit, classCount, c, a, b, t, changed, key;
    unsigned int mask, merged;
    SceneLink *link;
    i = 0;
    func_0011AF38(self->list58, 0x14);
    func_001D2770(frame);
    func_00151A38(&list);
    func_00151D80(self->source, stream, &list);
    for (; i < list.count; ++i) {
        SceneObject *child = list.items[i];
        VirtualEntry *entry = &child->vtable[9];
        entry->call((char *)child + entry->adjustment);
    }
    {
        int count = func_00118FF8(stream);
        pointer = &request;
        request.bytes = count * 8;
        pointer->alignment = 16;
        self->entryCount = count;
        self->entries = (SceneEntry *)func_001D2470(pointer);
    }
    for (i = 0; i < self->entryCount; ++i) {
        SceneEntry *entry = self->entries + i;
        entry->id = func_001191E0(stream);
        entry->ref = func_001191E0(stream);
    }
    for (i = 0; i < self->entryCount; ++i) {
        SceneEntry *entry = self->entries + i;
        switch (entry->ref) {
        case -1:
            entry->ref = -1;
            break;
        case 0x3B:
            entry->ref = -2;
            break;
        default:
            entry->ref = func_00239AB8(self, entry->ref);
            break;
        }
    }
    {
        int count = func_00118FF8(stream);
        j = 0;
        mask = 0;
        self->linkCount = count;
        request.bytes = count * 0x18;
        pointer->alignment = 16;
        self->links = (SceneLink *)func_001D2670(pointer);
    }
    for (; j < self->linkCount; ++j) {
        SceneLink *link = self->links + j;
        link->first = func_00239AB8(self, func_001191E0(stream));
        link->second = func_00239AB8(self, func_001191E0(stream));
        link->mask = func_001191E0(stream);
        link->extra = func_001191E0(stream);
        link->value = func_00119260(stream);
        key = func_001191E0(stream);
        if (key != -1) {
            for (i = 0; i < list.count; ++i) {
                if (list.items[i]->id == key) {
                    link->object = list.items[i];
                    break;
                }
            }
            if (!link->object) {
                --self->linkCount;
                --j;
                continue;
            }
        }
        mask |= link->mask & 0x7FFC;
    }
    request.bytes = self->linkCount * 0x18;
    pointer->alignment = 16;
    self->links = (SceneLink *)func_001D24D0(pointer, self->links);
    func_001519C8(self, stream);
    classCount = 0;
    for (bit = 4; bit <= 0x8000; bit <<= 1) {
        if (!(bit & mask))
            continue;
        for (k = 0; k < classCount; ++k)
            if (bit & classes[k])
                goto next;
        merged = mask;
        for (j = 0; j < self->linkCount; ++j) {
            link = &self->links[j];
            if (link->mask & bit)
                merged &= link->mask;
        }
        for (j = 0; j < self->linkCount; ++j) {
            link = &self->links[j];
            if ((link->mask & merged) && !(link->mask & bit))
                merged &= ~link->mask;
        }
        classes[classCount++] = merged;
    next:;
    }
    request.bytes = classCount * 8;
    pointer->alignment = 16;
    self->classCount = classCount;
    self->classes = (SceneClass *)func_001D2470(pointer);
    for (c = 0; c < self->classCount; ++c) {
        SceneClass *cls = self->classes + c;
        cls->mask = classes[c];
        request.bytes = self->entryCount * self->entryCount;
        pointer->alignment = 16;
        cls->table = (signed char *)func_001D2470(pointer);
        for (a = 0; a < self->entryCount; ++a)
            for (b = 0; b < self->entryCount; ++b)
                cls->table[a * self->entryCount + b] = (a == b) ? 0 : -1;
        t = 1;
        do {
            changed = 0;
            for (j = 0; j < self->linkCount; ++j) {
                SceneLink *link = self->links + j;
                if (!(link->mask & cls->mask))
                    continue;
                for (i = 0; i < self->entryCount; ++i) {
                    if (cls->table[i * self->entryCount + link->first] == t - 1 && cls->table[i * self->entryCount + link->second] < 0) {
                        cls->table[i * self->entryCount + link->second] = t;
                        changed = 1;
                    } else if ((link->mask & 1) && cls->table[i * self->entryCount + link->second] == t - 1 && cls->table[i * self->entryCount + link->first] < 0) {
                        cls->table[i * self->entryCount + link->first] = t;
                        changed = 1;
                    }
                }
            }
            ++t;
        } while (changed);
    }
    func_001D2798(frame, 2);
}
