// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Search the original fixed-stride record array.
typedef struct Record { int key; unsigned char rest[0x4]; } Record;
typedef struct State { unsigned char pad[0x50]; int count; Record *records; } State;
Record *func_00239AD8(State *state, int key)
{
    int count = state->count;
    int index = 0;
    if (count > 0) {
        do {
            Record *record = state->records + index;
            index++;
            if (record->key & key)
                return record;
        } while (index < count);
    }
    return 0;
}
