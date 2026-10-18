// SLY3_CFLAGS: -Os -G0
struct AllocationRequest { int bytes, alignment; };
struct StateRecord {
    int first;
    int second;
    int third;
};
struct BufferOwner {
    unsigned char prefix[0x4470];
    void *buffers[3];
    unsigned char gap447C[0x4634 - 0x447C];
    struct StateRecord *record;
    unsigned char gap4638[0x4654 - 0x4638];
    void *block;
};
extern unsigned char D_004BC230[];
extern unsigned char D_0036C700[];
void *func_001D2470(struct AllocationRequest *request);
void *func_001D2538(struct AllocationRequest *request);
void func_0011AD60(void *record, int size);
void func_002837A0(void *state);
void func_00184A08(void *context);
void func_0025AFD8(struct BufferOwner *owner)
{
    struct AllocationRequest request;
    int i;
    for (i = 0; i < 3; i++) {
        request.bytes = 0x4800;
        request.alignment = 0x10;
        owner->buffers[i] = func_001D2470(&request);
    }
    request.bytes = 0x8000;
    request.alignment = 0x10;
    owner->block = func_001D2538(&request);
    request.bytes = 0x28;
    request.alignment = 0x10;
    owner->record = func_001D2538(&request);
    owner->record->first = -1;
    owner->record->third = -1;
    func_0011AD60((char *)owner->record + 0x18, 0x14);
    func_002837A0(D_004BC230);
    func_00184A08(D_0036C700);
}
