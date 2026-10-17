// SLY3_CFLAGS: -Os -G0
struct SortedItem { unsigned char prefix[0x14C]; int key; };
struct SortedGame { unsigned char prefix[0x3EB4]; int counter; int count; struct SortedItem *items[5]; };
void *func_00291F38(void *destination, void *source, int bytes);
static inline void MoveUp(void *destination, void *source, int bytes)
{
    func_00291F38(destination, source, bytes);
}

void func_00165B88(struct SortedGame *game);
void func_0015AF48(struct SortedGame *game);
void func_00165C70(struct SortedGame *game, struct SortedItem *item)
{
    if(game->count >= 0 && game->count < 5) {
        int i;
        for(i = 0; i < game->count; i++) {
            if(game->items[i]->key < item->key) break;
        }
        MoveUp(&game->items[i + 1], &game->items[i], (game->count - i) * 4);
        game->items[i] = item;
        game->count++;
        game->counter++;
        func_00165B88(game);
        func_0015AF48(game);
    }
}
