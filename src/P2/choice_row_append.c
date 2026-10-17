// SLY3_CFLAGS: -Os -G0
struct ResourceChoice {
    int key;
    int word4;
    char reserved8[0x14 - 8];
    int word14, word18;
    int count;
    int ids[3];
};
struct ResourceChoices {
    char prefix[0x1AC];
    int count;
    struct ResourceChoice *rows;
    struct ResourceChoice *selected;
};
typedef char CheckResourceChoice44[sizeof(struct ResourceChoice) == 44 ? 1 : -1];
typedef char CheckResourceChoices1B8[sizeof(struct ResourceChoices) == 0x1B8 ? 1 : -1];
void func_001F9028(void *receiver);
void func_001F8FA8(void *receiver, int key, int word4)
{
    struct ResourceChoices *object = (struct ResourceChoices *)receiver;
    func_001F9028(receiver);
    if (object->count < 32) {
        struct ResourceChoice *row = &object->rows[object->count++];
        object->selected = row;
        row->key = key;
        row->word4 = word4;
        row->word14 = -1;
        row->word18 = -1;
        row->count = 0;
    }
}
