// Lookup wrapper: the key word may encode a supplied pointer under flag0x100.
void *func_0017E1D8(void *game, int flags, int key_word, void *owner, void *scope);
void *func_0017E1B8(void *game, int flags, int key_word, void *owner) {
    return func_0017E1D8(game, flags, key_word, owner, 0);
}
