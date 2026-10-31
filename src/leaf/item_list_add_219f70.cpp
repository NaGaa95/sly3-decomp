// Refresh the five-slot item list from the input reference and append the item (resetting the count when the list is full).
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
class ListReference {
public:
    CRef value;
    ListReference() { value.tag = -1; }
    ListReference(const ListReference &) __asm__("func_0012AF00");
    ListReference &operator=(const ListReference &) __asm__("func_0012B3B0");
    void Drop() __asm__("func_0012BC20");
    ~ListReference() { Drop(); }
};
struct Item;
struct ItemList {
    unsigned char opaque00[0x44];
    Item *items[5];
    unsigned int count;
    unsigned char opaque5C[0xA8 - 0x5C];
    int flag;
};
extern "C" {
int func_0021A710(void *object);
void func_0021A1C8(ItemList *list, Item *item);
ListReference GatherItems(CRef *, int, int, unsigned int *, Item **) __asm__("func_0024B330");
}
extern "C" void func_00219F70(ItemList *list, Item *item, CRef *input, int flag)
{
    if (func_0021A710(list)) return;
    if (item) {
        ListReference result;
        list->count = 0;
        result = GatherItems(input, 0x2058, 5, &list->count, list->items);
        if (list->count >= 5) {
            list->count = 0;
            return;
        }
        list->items[list->count++] = item;
        list->flag = flag;
        func_0021A1C8(list, item);
    }
}
