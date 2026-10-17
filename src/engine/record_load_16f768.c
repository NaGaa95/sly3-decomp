// SLY3_CFLAGS: -Os -G0
struct LoadRequest { int bytes; int alignment; };
struct LoadRecord { int id; int kind; int first; int second; unsigned char payload[0x40]; int last; };
struct LoadOwner { unsigned char prefix[0x40]; int count; struct LoadRecord *records; };
void *func_001D2770(void *receiver);
void func_001D2798(void *receiver, int flags);
void *func_001D2670(struct LoadRequest *request);
void *func_001D2538(struct LoadRequest *request);
void func_001C7D98(void *owner, void *stream);
int func_00118FF8(void *stream);
int func_001191E0(void *stream);
int func_00119128(void *stream);
void func_00119948(void *stream, void *destination);
int func_00162A68(int value);
void func_0016F768(struct LoadOwner *owner, void *stream)
{
    unsigned char frame[16];
    struct LoadRequest request;
    struct LoadRequest *pointer;
    struct LoadRecord *loaded, *destination, *stored;
    int count, i, j, skip;
    i = 0;
    func_001C7D98(owner, stream);
    count = func_00118FF8(stream);
    owner->count = count;
    func_001D2770(frame);
    pointer = &request;
    request.bytes = count * 0x54;
    pointer->alignment = 0x10;
    loaded = (struct LoadRecord *)func_001D2670(pointer);
    for(i = 0; i < count; i++) {
        struct LoadRecord *record = loaded + i;
        record->id = func_001191E0(stream);
        record->kind = func_00119128(stream);
        record->last = func_00119128(stream);
        record->first = func_001191E0(stream);
        record->second = func_001191E0(stream);
        func_00119948(stream, record->payload);
        skip = 0;
        switch(record->first) {
        case 0x712:
            skip = func_00162A68(0) == 0;
            break;
        case 0x70E:
            skip = func_00162A68(0);
            break;
        }
        if(skip) {
            record->id = -1;
            owner->count--;
        }
    }
    request.bytes = owner->count * 0x54;
    pointer->alignment = 0x10;
    stored = (struct LoadRecord *)func_001D2538(pointer);
    owner->records = stored;
    destination = stored;
    for(j = 0; j < count; j++) {
        struct LoadRecord *record = loaded + j;
        if(record->id != -1) {
            *destination = *record;
            destination++;
        }
    }
    func_001D2798(frame, 2);
}
