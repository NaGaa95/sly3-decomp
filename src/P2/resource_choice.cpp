// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
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
    ResourceChoice *rows;
    ResourceChoice *selected;
};
struct A;
struct P;
typedef char CheckResourceChoice44[sizeof(ResourceChoice) == 44 ? 1 : -1];
typedef char CheckResourceChoices1B8[sizeof(ResourceChoices) == 0x1B8 ? 1 : -1];
extern "C" {
void func_0023FFA0(A *receiver);
void func_0023FE38(P *receiver, int key);
}

extern "C" void func_001F9078(void *receiver, int key)
{
    ResourceChoices *object = (ResourceChoices *)receiver;
    for (int index = 0; ; ++index) {
        if (index >= object->count) {
            object->selected = object->rows;
            break;
        }
        ResourceChoice *row = &object->rows[index];
        if (key == row->key) {
            object->selected = row;
            break;
        }
    }
    func_0023FFA0((A *)receiver);
    for (int index = 0; index < object->selected->count; ++index)
        func_0023FE38((P *)receiver, object->selected->ids[index]);
}

extern "C" ResourceChoice *func_001F9128(void *receiver)
{
    return ((ResourceChoices *)receiver)->selected;
}
