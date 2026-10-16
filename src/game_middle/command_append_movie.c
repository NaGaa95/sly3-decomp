// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct E { int k; int a[6]; };
struct L;
struct CommandInput64 { int words[16]; };
extern struct E *func_001C7068(struct L *, int);
static __inline__ int UsableCommandInput(const struct CommandInput64 *record)
{
    if (!record)
        return 0;
    return record->words[1] != record->words[15];
}
void func_001C70D8(struct L *runtime, const struct CommandInput64 *record)
{
    if (UsableCommandInput(record))
        func_001C7068(runtime, 0)->a[0] = (int)record;
}
