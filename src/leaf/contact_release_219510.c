// SLY3_CFLAGS: -Os -G0
struct ContactVirtualEntry { short delta; short unused; void *method; };
struct ContactObject { char prefix[12]; struct ContactVirtualEntry *vtable; };
struct ContactPair { void *resource; struct ContactPair *next; struct ContactPair *other; struct ContactObject *object; };
struct ContactNode { char prefix[0x64]; struct ContactPair *pairs; };
struct ContactBinding {
    char prefix[12];
    struct ContactVirtualEntry *vtable;
    char gap10[0xDC - 0x10];
    struct ContactNode *node;
    char gapE0[0x130 - 0xE0];
    int groupCount;
    int groups[4];
    int kindCount;
    int kinds[1];
};
extern char D_00475480[];
void func_0023E068(void *self);
int func_001C8768(void *object, int group);
int func_0013B500(void *object, int kind);
void func_0023E228(struct ContactObject *object);
void func_001CBAA0(void *game, void *resource);
#define CONTACT_CALL_PAIR(object, other) ((void (*)(void *, void *))(object)->vtable[58].method)((char *)(object) + (object)->vtable[58].delta, (other))
#define CONTACT_CALL_PREDICATE(object) ((int (*)(void *))(object)->vtable[66].method)((char *)(object) + (object)->vtable[66].delta)
void func_00219510(struct ContactBinding *self)
{
    struct ContactPair *pair;
    func_0023E068(self);
    for (pair = self->node->pairs; pair; pair = pair->next) {
        struct ContactObject *object;
        int matched = 0;
        int i;
        int j;
        if (!pair->resource)
            continue;
        object = pair->object;
        for (i = 0; i < self->groupCount; i++) {
            if (func_001C8768(object, self->groups[i])) {
                matched = 1;
                break;
            }
        }
        if (!matched) {
            for (j = 0; j < self->kindCount; j++) {
                if (func_0013B500(object, self->kinds[j])) {
                    matched = 1;
                    break;
                }
            }
        }
        if (!matched)
            continue;
        CONTACT_CALL_PAIR(self, object);
        CONTACT_CALL_PAIR(object, self);
        if (!CONTACT_CALL_PREDICATE(object))
            func_0023E228(object);
        func_001CBAA0(D_00475480, pair->resource);
        pair->other->resource = 0;
        pair->resource = 0;
    }
}
