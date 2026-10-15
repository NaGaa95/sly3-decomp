// Return the last record matching the actual integer mode selector in the original44-byte array.
// Complete original inputs, return boundary and initialized sections are independently verified.
// SLY3_CFLAGS: -Os -G0
struct Record {
    int identifier;
    char rest[0x28];
};
struct S {
    char prefix[0x1D4];
    struct Record *records;
    int count;
};
struct Record *func_002151A0(struct S *p,int identifier) {
    struct Record *result=0;
    int index;
    for(index=0;index<p->count;++index) {
        struct Record *entry=&p->records[index];
        if(entry->identifier==identifier)result=entry;
    }
    return result;
}
