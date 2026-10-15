// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// The original incoming context occupies a0; chain and head use a1/a2.
// Prepend the complete chain while preserving its existing node links.
#include "m2c_prelude.h"
typedef struct Node { u8 reserved[0xAC]; struct Node *next; } Node;
void func_001CDD30(u32 context, Node *chain, Node **head) {
    Node *last;
    if (chain != NULL) {
        last = chain;
        if (chain->next != NULL) {
            do {
                last = last->next;
            } while (last->next != NULL);
        }
        last->next = *head;
        *head = chain;
    }
}
