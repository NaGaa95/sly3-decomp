// Rebuild the slot table of the item list: for every active item append a slot holding its measured value (kind 2 or 3) or zero, then refresh the list with mode 2 (enabled, non-empty, not blocked) or mode 8.
// SLY3_CFLAGS: -Os -G0 -ffast-math
struct Item {
    unsigned char opaque000[0x508];
    float firstA, firstB;
    float secondA, secondB;
    int kind;
};
struct Slot { struct Item *item; int value; };
struct ItemList {
    unsigned char opaque00[0x44];
    struct Item *items[5];
    int count;
    unsigned char opaque5C[0x6C - 0x5C];
    struct Slot slots[5];
    int slotCount;
    int total;
    int pad9C;
    unsigned char opaqueA0[4];
    int enabled;
    int blocked;
};
float func_0011E940(float a, float b);
void func_00219A18(struct ItemList *list, int mode);
void func_0021A300(struct ItemList *list)
{
    int i;
    struct Item *item;
    struct Slot *slot;
    list->slotCount = 0;
    list->total = 0;
    list->pad9C = 0;
    for (i = 0; i < list->count; i++) {
        item = list->items[i];
        if (item->kind) {
            slot = &list->slots[list->slotCount++];
            switch (item->kind) {
            case 3:
                slot->value = (int)func_0011E940(item->secondA, item->secondB);
                break;
            case 2:
                slot->value = (int)func_0011E940(item->firstA, item->firstB);
                break;
            default:
                slot->value = 0;
                break;
            }
            slot->item = item;
        }
    }
    if (list->enabled && list->slotCount > 0 && !list->blocked) func_00219A18(list, 2);
    else func_00219A18(list, 8);
}
