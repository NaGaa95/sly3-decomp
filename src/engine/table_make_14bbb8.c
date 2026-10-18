// SLY3_CFLAGS: -Os -G0
struct TableRequest { int bytes, alignment; };
struct TableRecord { unsigned char prefix[0xA0]; int quarter; void *second; void *first; };
extern unsigned char D_00479BF8[];
struct TableRecord *func_0014BB50(void *key);
void *func_001D27F0(int bytes);
void func_0011ADA8(void *list, void *node);
void *func_001D2470(struct TableRequest *request);
struct TableRecord *func_0014BBB8(void *owner, int count)
{
    struct TableRequest request;
    int quarter = count / 4;
    struct TableRecord *record = func_0014BB50(owner);
    if(!record) {
        record = func_001D27F0(0x170);
        func_0011ADA8(D_00479BF8, record);
        request.alignment = 0x10;
        request.bytes = count * 0x50;
        record->first = func_001D2470(&request);
        record->quarter = quarter;
        request.bytes = quarter << 6;
        request.alignment = 0x10;
        record->second = func_001D2470(&request);
    }
    return record;
}
