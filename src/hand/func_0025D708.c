// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct Node { unsigned int next, previous; } Node;
typedef struct List { unsigned char pad[0x3C]; unsigned int head; } List;
typedef struct State { unsigned char pad[0x464C]; int count; } State;
// Bit zero tags the terminator of this intrusive free-node chain.
void func_0025D708(State *state, List *list)
{
    unsigned int head = list->head;
    if ((head ^ 1) & 1) {
        Node *node = (Node *)head;
        list->head = node->next;
        node->previous = node->next = 0;
        state->count++;
    }
}
