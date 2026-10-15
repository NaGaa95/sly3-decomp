// SLY3_CFLAGS: -Os -G0
struct Holder;
struct Record { void *key; int words[4]; };
struct Record *func_00170528(struct Holder *, void *);
int func_00170500(struct Holder *holder, void *key)
{
    struct Record *record = func_00170528(holder, key);
    if (record)
        return record->words[1];
    return -1;
}
