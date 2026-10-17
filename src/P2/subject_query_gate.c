// SLY3_CFLAGS: -Os -G0
struct Query {
    short delta;
    short unused;
    int (*call)(void *);
};
struct Subject {
    unsigned char prefix[0xC];
    struct Query *queries;
    unsigned char gap[0x380 - 0x10];
    int mode;
};
int func_001F42E8(struct Subject *, void *);
int func_00207D68(struct Subject *subject, void *context)
{
    if (subject->queries[81].call((char *)subject + subject->queries[81].delta))
        return 1;
    if (subject->mode == 4)
        return 1;
    return func_001F42E8(subject, context);
}
