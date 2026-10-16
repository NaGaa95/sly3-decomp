// SLY3_CFLAGS: -Os -G0
#include "control_chain_api.h"
typedef struct ControlChainNode {
    int kind;
    int key;
    unsigned char unaccessed8[0x14];
    struct ControlChainNode *next;
} ControlChainNode;

typedef struct ControlChainOwner {
    unsigned char unaccessed0[0x40];
    ControlChainNode *head;
} ControlChainOwner;

extern unsigned char D_00475480[];
void *func_0017E1B8(void *game, int flags, int key, void *context);
int func_00197118(void *object);
void func_00231948(void *object);

void func_001971C8(void *owner)
{
    ControlChainNode *node;

    for (node = ((ControlChainOwner *)owner)->head; node; node = node->next) {
        switch (node->kind) {
        case 6: {
            void *object;
            int flags = 5;
            if (owner)
                flags = 4;
            object = func_0017E1B8(D_00475480, flags, node->key, owner);
            if (object && func_00197118(object) == -1)
                func_00231948(object);
            break;
        }
        case 0: {
            int flags = 5;
            if (owner)
                flags = 4;
            owner = func_0017E1B8(D_00475480, flags, node->key, owner);
            break;
        }
        }
    }
}
