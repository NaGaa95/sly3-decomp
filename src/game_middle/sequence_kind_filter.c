// SLY3_CFLAGS: -Os -G0
struct SequenceKindRow { int kind, enabled; };
struct SequenceKindFilter {
    char prefix[0x130];
    int count;
    struct SequenceKindRow *rows;
};
int func_0013B500(void *object, int kind);

int func_001E4F40(struct SequenceKindFilter *filter, void *object)
{
    int i;
    for (i = 0; i < filter->count; i++) {
        struct SequenceKindRow *row = &filter->rows[i];
        if (!row->enabled) continue;
        if (func_0013B500(object, row->kind)) return 1;
    }
    return 0;
}
