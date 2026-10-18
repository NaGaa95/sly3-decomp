// SLY3_CFLAGS: -Os -G0
struct StateRecord { char prefix[8]; int state; char padC[4]; int key; char pad14[0x6C - 0x14]; };
struct RecordGame { char prefix[0x462C]; int count; struct StateRecord *records; };
extern struct RecordGame D_00475480;
void func_00169500(void *unused, int key, int state)
{
    int i;
    for(i = 0; i < D_00475480.count; i++) {
        struct StateRecord *record = D_00475480.records + i;
        if(record->key == key) {
            record->state = state;
            break;
        }
    }
}
