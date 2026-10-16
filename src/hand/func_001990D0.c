// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct Record { void *key; unsigned char rest[0x2C]; } Record;
typedef struct State { unsigned char pad[0x4C]; int count; Record *records; } State;
#include "path_task_api.h"
void *func_001990D0(void *state_address, void *key)
{
    State *state = state_address;
    int count = state->count;
    int index = 0;
    if (count > 0) {
        do {
            Record *record = state->records + index;
            index++;
            if (record->key == key)
                return record;
        } while (index < count);
    }
    return 0;
}
