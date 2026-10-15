// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct AnimationCleanupMethod { short delta,unused; void (*method)(); };
struct AnimationCleanupReference {
    unsigned char prefix[12];
    struct AnimationCleanupMethod *methods;
};
struct AnimationCleanupPair {
    unsigned char prefix[0xA4];
    unsigned int wordA4,wordA8;
};
struct AnimationCleanupChannel {
    unsigned char prefix[0xA8];
    struct AnimationCleanupPair *pair;
};
struct AnimationCleanupTask {
    unsigned char prefix[8];
    struct AnimationCleanupChannel *channel;
    unsigned char unusedC[0x14];
    unsigned int word20;
};
void func_00137B00(void *);
void func_0012F2C8(void);
void func_00137628(void *storage)
{
    struct AnimationCleanupReference **slot=(struct AnimationCleanupReference **)storage;
    struct AnimationCleanupReference *original=*slot;
    if(original) {
        func_00137B00(original);
        if(*slot==original) {
            struct AnimationCleanupReference *current=*slot;
            ((void (*)(void *))current->methods[2].method)
                ((char *)current+current->methods[2].delta);
            *slot=0;
        }
    }
}
void func_00138DF0(void *receiver)
{
    struct AnimationCleanupTask *task=(struct AnimationCleanupTask *)receiver;
    if(task->word20) {
        task->channel->pair->wordA4=0;
        task->channel->pair->wordA8=0;
    } else {
        func_0012F2C8();
    }
}
