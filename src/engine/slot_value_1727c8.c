// SLY3_CFLAGS: -Os -G0
struct SlotPair { int value, other; };
struct SlotRecord { struct SlotPair pairs[30]; };
struct SlotTable { unsigned char prefix[0x5C]; int count; struct SlotRecord *records; };
void func_001727C8(struct SlotTable *table, int index, int value)
{
    if(table->count) {
        struct SlotRecord *last = &table->records[table->count - 1];
        last->pairs[index].value = value;
    }
}
