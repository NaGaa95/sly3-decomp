// SLY3_CFLAGS: -Os -G0
struct Mask { unsigned int words[4]; };
struct Record { unsigned char prefix[0x10]; struct Mask mask; };
struct Table { unsigned char prefix[0x4D0]; int count; unsigned char gap4D4[0xC]; struct Record records[1]; };
struct Record *func_00255418(struct Table *table,struct Mask mask);
void func_00254BB8(struct Record *record,struct Table *table);
struct Record *func_002554C0(struct Table *table,struct Mask mask)
{
    struct Record *record=func_00255418(table,mask);
    if(!record) {
        struct Record *slot=&table->records[table->count++];
        slot->mask=mask;
        record=slot;
    }
    func_00254BB8(record,table);
    return record;
}
