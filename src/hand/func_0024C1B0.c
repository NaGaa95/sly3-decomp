// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct Node { unsigned char pad[0xF8]; int value; } Node;
typedef struct State { unsigned char pad[0x30]; int count; Node *nodes[0]; } State;
// Reset the field on each current member; the count is reloaded each iteration.
void func_0024C1B0(State *state)
{
    int index = 0;
    if (state->count > 0) {
        do {
            Node *node = state->nodes[index];
            index++;
            node->value = 0;
        } while (index < state->count);
    }
}
