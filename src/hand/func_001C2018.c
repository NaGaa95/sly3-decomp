// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original Sly 3 state and record semantics.
typedef struct Record { int first, second, third, fourth; } Record;
typedef struct State { int key, other; unsigned char pad[0x10]; int middle; unsigned char gap[0x10]; Record records[14]; } State;
void func_001C2018(State *state, int key)
{
    Record *record = state->records;
    int remaining = 13;
    state->key = key;
    state->other = -1;
    state->middle = -1;
    do {
        remaining--;
        record->first = record->third = -1;
        record++;
    } while (remaining >= 0);
}
