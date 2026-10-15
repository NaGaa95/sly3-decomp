// Return the parallel20-byte record corresponding to the first matching scalar key in the original40-byte key array.
// Complete original body, actual inputs and every initialized section are independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct KeyRecord {
    unsigned int identifier;
    char rest[0x24];
};
struct ValueRecord {
    char fields[0x14];
};
struct Receiver {
    char prefix[0xA8];
    int count;
    struct ValueRecord *values;
    const struct KeyRecord *keys;
};
struct ValueRecord *func_0023FDE8(const struct Receiver *p, unsigned int identifier) {
    int index;
    for (index = 0; index < p->count; ++index) {
        const struct KeyRecord *entry = p->keys + index;
        if (entry->identifier == identifier) return &p->values[index];
    }
    return 0;
}
