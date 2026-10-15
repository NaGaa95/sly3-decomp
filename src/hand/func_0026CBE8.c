// Return whether an actual entry pointer is present in any object chain of the original outer list.
// Complete original body, actual inputs and every initialized section are independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct Object {
    char prefix[0x48];
    const void *entry;
    char middle[0x60];
    const struct Object *next;
};
struct List {
    const struct Object *object;
    const struct List *next;
};
int func_0026CBE8(const struct List *list, const void *entry) {
    while (list) {
        const struct Object *object = list->object;
        while (object) {
            if (object->entry == entry) return 1;
            object = object->next;
        }
        list = list->next;
    }
    return 0;
}
