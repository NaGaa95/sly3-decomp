// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"
typedef struct NotifyEntry {
    float time;
    void *receiver;
    ScriptNode *node;
    int id;
    struct NotifyEntry *next;
} NotifyEntry;
typedef struct NotifyQueueView {
    char prefix[0x3F20];
    NotifyEntry *first;
    char unaccessed[8];
    unsigned char pool;
} NotifyQueueView;
void func_0011AE28(void *list, NotifyEntry *entry);
void func_0011E1F0(void *pool, void *entry);
void func_002BA840(ScriptNode *node, int flags);

void func_0013BAC8(NotifyQueueView *game, int id)
{
    NotifyEntry *entry;
    if (id == -1)
        return;
    for (entry = game->first; entry; entry = entry->next) {
        if (entry->id == id) {
            ScriptNode *node;
            func_0011AE28(&game->first, entry);
            node = entry->node;
            if (--node->ref.word2 == 0 && node)
                func_002BA840(node, 3);
            func_0011E1F0(&game->pool, entry);
            break;
        }
    }
}
