// SLY3_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original Sly 3 state and record semantics.
typedef struct Record { int key, zero, invalid, active; } Record;
typedef struct State { unsigned char pad[0x414]; Record records[8]; int count; unsigned char gap[8]; int enabled; } State;
void func_001F1780(State *state, int key)
{
    int count = state->count;
    if (count <= 0 || state->enabled) {
        Record *record = &state->records[count];
        state->count = count + 1;
        record->key = key;
        record->zero = 0;
        record->invalid = -1;
        record->active = 1;
    }
}
