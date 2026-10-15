// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct SavedPropertyEntry {
    short key;
    signed char kind;
    unsigned char bitCount;
    unsigned short offset, child, sibling;
};
struct SavedPropertyTrie { int count; SavedPropertyEntry *entries; char hash[1]; };
typedef char CheckSavedEntry10[sizeof(SavedPropertyEntry) == 10 ? 1 : -1];
extern "C" {
extern const char D_00325F40[]; // focus_count
extern const char D_00325F50[]; // is_complete
extern const char D_00325F60[]; // time_played
extern const char D_00325F70[]; // suck_value
extern const char D_00325F80[]; // complete_count
extern const char D_00325F90[]; // state
extern const char D_00325F30[]; // from_memcard
int func_0021CB20(void *, const char *);
void func_0021C860(SavedPropertyTrie *trie, unsigned char *buffer)
{
    int focus = func_0021CB20(trie->hash, D_00325F40);
    int complete = func_0021CB20(trie->hash, D_00325F50);
    int time = func_0021CB20(trie->hash, D_00325F60);
    int suck = func_0021CB20(trie->hash, D_00325F70);
    int completions = func_0021CB20(trie->hash, D_00325F80);
    int state = func_0021CB20(trie->hash, D_00325F90);
    int fromCard = func_0021CB20(trie->hash, D_00325F30);
    for (int i = 0; i < trie->count; ++i) {
        SavedPropertyEntry *entry = &trie->entries[i];
        if (entry->key == -1) continue;
        if (entry->key == focus || entry->key == completions || entry->key == state)
            *(unsigned int *)(buffer + entry->offset) = 0;
        if (entry->key == complete || entry->key == fromCard)
            buffer[entry->offset] = 0;
        if (entry->key == time || entry->key == suck)
            *(unsigned int *)(buffer + entry->offset) = 0;
    }
}
}
