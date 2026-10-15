// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct Record { int first, second, active; } Record;
typedef struct State { unsigned char pad[0x244]; Record records[4]; unsigned int count; } State;
// Append one pair to the four-entry queue and mark it active.
void func_00146EA8(State *state, int first, int second)
{
    unsigned int count = state->count;
    if (count < 4) {
        Record *record = &state->records[state->count++];
        record->first = first;
        record->second = second;
        record->active = 1;
    }
}
