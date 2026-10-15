// The original queue holds four-byte-aligned 28-byte records.
#include "m2c_prelude.h"
typedef struct Record { s32 fields[7]; } Record;
typedef struct Queue { u8 unknown[0xA]; s16 count; Record *entries; } Queue;
typedef struct State { u8 unknown[0x20]; Queue *queue; } State;
void func_001FD250(State *state, const Record *input) {
    Queue *queue = state->queue;
    if (queue->count < 32) {
        queue->entries[queue->count++] = *input;
    }
}
