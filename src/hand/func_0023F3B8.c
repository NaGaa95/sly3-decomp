// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Search the original fixed-stride record array.
typedef struct Record { unsigned char pad[0x10]; int key; unsigned char rest[0xBC]; } Record;
typedef struct State { unsigned char pad[0xD0]; int count; Record *records; } State;
Record *func_0023F3B8(State *state, int key)
{
    int count = state->count;
    int index = 0;
    if (count > 0) {
        do {
            Record *record = (Record *)(index * sizeof(Record) + (unsigned int)state->records);
            index++;
            if (record->key == key)
                return record;
        } while (index < count);
    }
    return 0;
}
