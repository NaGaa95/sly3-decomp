// SLY3_CFLAGS: -Os -G0
struct CollisionFilterOwner {
    char unaccessed[0xDC];
    void *collision;
};
struct CollisionFilterCandidate {
    int word0;
    struct CollisionFilterOwner *owner;
};
struct CollisionFilterList {
    int count;
    void **items;
};
int func_0025CDD0(void *source, struct CollisionFilterCandidate *candidate);

int func_001BBC28(void *context, void *value)
{
    struct CollisionFilterList *list = (struct CollisionFilterList *)context;
    struct CollisionFilterCandidate *candidate = (struct CollisionFilterCandidate *)value;
    int i;
    if (!func_0025CDD0(list->items[0], candidate))
        return 0;
    for (i = 0; i < list->count; ++i)
        if (list->items[i] == candidate->owner->collision)
            return 0;
    return 1;
}
