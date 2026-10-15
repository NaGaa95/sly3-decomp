// Forward the real owner and caller-owned pointer output; scope defaults inside17DEC0.
int func_0017DEC0(void *game, int flags, int key_word, void *owner, void *scope, int limit, void **output);
int func_0017DE98(void *game, int flags, int key_word, void *owner, int limit, void **output) {
    return func_0017DEC0(game, flags, key_word, owner, 0, limit, output);
}
