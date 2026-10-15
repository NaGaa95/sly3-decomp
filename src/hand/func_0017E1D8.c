// Return the first pointer written by the count-returning lookup helper.
int func_0017DEC0(void *game, int flags, int key_word, void *owner, void *scope, int limit, void **output);
void *func_0017E1D8(void *game, int flags, int key_word, void *owner, void *scope) {
    void *node;
    if (!func_0017DEC0(game, flags | 0x200, key_word, owner, scope, 1, &node)) return 0;
    return node;
}
