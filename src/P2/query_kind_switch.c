// SLY3_CFLAGS: -Os -G0
struct Record {
    int first;
    unsigned char gap[0x1C - 4];
    unsigned int kind;
};
struct Item {
    unsigned char prefix[0x1C];
    struct Record *record;
};
struct Query {
    unsigned char prefix[4];
    struct Item *item;
    unsigned char gap[0x60 - 8];
    void *target;
};
int func_0013B500(void *, int);
int func_002029E8(struct Query *query)
{
    switch (query->item->record->kind) {
    case 7:
        return 1;
    case 1: {
        int first = query->item->record->first;
        int result = 0;
        if (first == 1) {
            if (query->target)
                result = func_0013B500(query->target, 0x2D) ? first : 0;
        }
        return result;
    }
    case 0:
    case 2:
    case 4:
        return query->target != 0;
    }
    return 0;
}
