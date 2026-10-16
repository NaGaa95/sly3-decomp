// SLY3_CFLAGS: -Os -G0
struct PendingReorderNode { void *unaccessed; struct PendingReorderNode *next; };
struct PendingReorderList {
    struct PendingReorderNode *first, *last;
    int link_offset;
};
struct PendingReorderGame {
    char prefix[0x3DE8];
    struct PendingReorderList handles;
    struct PendingReorderNode *handle_cursor;
    char unaccessed3DF8[0x3E50-0x3DF8];
    struct PendingReorderList queries;
    struct PendingReorderNode *query_cursor;
};
int func_0011B0C0(void *list, void *node);
void func_0011B028(void *list, void *node);
void func_0011AFC0(void *list, void *before, void *node);

void func_0015ADA0(struct PendingReorderGame *game, struct PendingReorderNode *node)
{
    struct PendingReorderList *list = &game->handles;
    if (func_0011B0C0(list, node)) {
        if (game->handle_cursor == node)
            game->handle_cursor = node->next;
        func_0011B028(list, node);
    }
    func_0011AFC0(list, game->handle_cursor, node);
}

void func_0015B6B0(struct PendingReorderGame *game, struct PendingReorderNode *node)
{
    struct PendingReorderList *list = &game->queries;
    if (func_0011B0C0(list, node)) {
        if (game->query_cursor == node)
            game->query_cursor = node->next;
        func_0011B028(list, node);
    }
    func_0011AFC0(list, game->query_cursor, node);
}
