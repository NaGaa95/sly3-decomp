// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct SCENE_OBJECT;
struct O;
struct BucketInitializerPrefix {
    char unused00[0x3C];
    unsigned int flags;
};
void func_001C7340(struct SCENE_OBJECT *);
void func_001C9118(struct O *, int);
void func_001C4920(void *, int, const int *, int, const int *);

void func_001C4870(struct SCENE_OBJECT *object)
{
    struct BucketInitializerPrefix *prefix = (struct BucketInitializerPrefix *)object;
    unsigned int flags;
    func_001C7340(object);
    func_001C9118((struct O *)object, 1);
    flags = prefix->flags;
    if ((flags ^ 1) & 1)
        *(unsigned int *)flags |= 2;
    else
        prefix->flags = flags | 2;
    {
        int included[6] = {49, 111, 102, 89, 34, 113};
        int excluded = 73;
        func_001C4920(object, 6, included, 1, &excluded);
    }
}
