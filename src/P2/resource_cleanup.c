// SLY3_CFLAGS: -Os -G0
struct AttachmentRetainMethod { short adjustment, reserved; void *function; };
struct AttachmentRetainedView {
    unsigned char prefix[0xC];
    struct AttachmentRetainMethod *table;
};
struct AttachmentApplyRecord {
    int kind;
    void *resource;
    struct AttachmentRetainedView *retained;
    int flags;
};
void func_00137628(void *storage);
void func_0023AC58(void *storage);
void func_002595D8(void *receiver);

void func_00254E18(struct AttachmentApplyRecord *record)
{
    switch (record->kind) {
    case -1:
        break;
    case 0:
    case 2:
        func_00137628(&record->retained);
        break;
    case 1:
        func_0023AC58(&record->retained);
        break;
    case 3:
        if (record->retained) {
            func_002595D8(record->retained);
            ((void (*)(void *))record->retained->table[2].function)
                ((char *)record->retained + record->retained->table[2].adjustment);
            record->retained = 0;
        }
        break;
    }
}
