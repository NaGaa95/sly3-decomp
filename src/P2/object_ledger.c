// SLY3_CFLAGS: -Os -G0
struct LedgerObjectView {
    unsigned char prefix3C[0x3C];
    unsigned int record_word;
};

struct ObjectLedgerEntry {
    unsigned int saved_word;
    struct LedgerObjectView *object;
};

struct ObjectLedgerView {
    unsigned char prefix4648[0x4648];
    int count;
    int removed;
    int *cursor;
    struct ObjectLedgerEntry *entries;
};

typedef char ObjectLedgerEntryMustBe8[sizeof(struct ObjectLedgerEntry) == 8 ? 1 : -1];
typedef char ObjectLedgerEntryMustAlign4[__alignof__(struct ObjectLedgerEntry) == 4 ? 1 : -1];

void func_0025D5E8(struct ObjectLedgerView *ledger, struct LedgerObjectView *object)
{
    struct ObjectLedgerEntry *entry;
    if (object->record_word & 0x80)
        return;
    if (ledger->count >= 4096 ||
        0.1f < (float)ledger->removed / (float)ledger->count) {
        struct ObjectLedgerEntry *read = ledger->entries;
        struct ObjectLedgerEntry *end = read + ledger->count;
        struct ObjectLedgerEntry *tracked = ledger->cursor ? read + *ledger->cursor : 0;
        struct ObjectLedgerEntry *write = read;
        for (; read < end; ++read) {
            if (read == tracked)
                tracked = write;
            if (read->object) {
                read->object->record_word = (unsigned int)write;
                *write++ = *read;
            }
        }
        ledger->removed = 0;
        ledger->count = write - ledger->entries;
        if (ledger->cursor)
            *ledger->cursor = tracked - ledger->entries;
    }
    entry = &ledger->entries[ledger->count++];
    entry->object = object;
    entry->saved_word = object->record_word;
    object->record_word = (unsigned int)entry;
}
