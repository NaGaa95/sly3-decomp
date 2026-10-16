// SLY3_CFLAGS: -Os -G0
struct TaggedRecordPayload {
    char prefix[0x20];
    unsigned int word20;
};
struct TaggedRecord {
    int kind;
    union { unsigned int word; struct TaggedRecordPayload *pointer; } value;
};
int func_0019B208(const struct TaggedRecord *left, const struct TaggedRecord *right)
{
    if (left->kind!=right->kind)return 0;
    switch (left->kind) {
    case 9: case 10: case 11:
        return left->value.pointer->word20==right->value.pointer->word20;
    case 4: return left->value.word==right->value.word;
    case 5: return left->value.word==right->value.word;
    case 3: return left->value.word==right->value.word;
    case 2: return left->value.word==right->value.word;
    case 13: return left->value.word==right->value.word;
    case 16: return left->value.word==right->value.word;
    case 6: return left->value.word==right->value.word;
    case 21: return left->value.word==right->value.word;
    }
    return 1;
}
