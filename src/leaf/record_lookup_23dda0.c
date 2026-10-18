// SLY3_CFLAGS: -Os -G0
struct ModelRecord {
    unsigned char prefix[0x94];
    int kind;
    int unknown98;
    int identity;
    unsigned char tail[0x60];
};
struct ModelRecordOwner {
    unsigned char prefix[0x40];
    int count;
    struct ModelRecord *records;
};
void *func_0023DDA0(void *receiver, int identity, int kind)
{
    struct ModelRecordOwner *owner = receiver;
    int count = owner->count;
    int i;
    for (i = 0; i < count; i++) {
        struct ModelRecord *record =
            (struct ModelRecord *)(i * sizeof(struct ModelRecord) + (int)owner->records);
        if (record->identity == identity && record->kind == kind)
            return record;
    }
    return 0;
}
