// Report whether the attached record exists and has reached the state where its result code equals 2.
// SLY3_CFLAGS: -Os -G0
struct AttachedRecord {
    char opaque00[0x48];
    int state;
    char opaque4C[8];
    int result;
};
struct Receiver {
    char opaque00[0x34];
    struct AttachedRecord *record;
};

int func_00221A20(struct Receiver *receiver)
{
    struct AttachedRecord *record = receiver->record;
    if (record == 0) return 0;
    if (record->state != 2) return 0;
    return record->result == 2;
}
