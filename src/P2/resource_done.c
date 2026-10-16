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
struct AttachmentCompletionWord { unsigned char prefix[0x30]; unsigned int value; };
int func_00138AC8(void *);
int func_00239CC0(void *);
int func_00259628(void *);

int func_00254EB8(struct AttachmentApplyRecord *record)
{
    int complete;
    switch (record->kind) {
    case 0:
    case 2:
        complete = 0;
        if (!record->retained || func_00138AC8(record->retained))
            complete = 1;
        break;
    case 1:
        complete = 0;
        if (!record->retained || func_00239CC0(record->retained) ||
            !((struct AttachmentCompletionWord *)record->retained)->value)
            complete = 1;
        break;
    case 3:
        complete = 0;
        if (!record->retained || func_00259628(record->retained))
            complete = 1;
        break;
    case -1:
    default:
        complete = 1;
        break;
    }
    return complete;
}
