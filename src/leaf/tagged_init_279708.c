// SLY3_CFLAGS: -Os -G0
struct Object {
    char prefix[0x3C];
    unsigned int taggedFlags;
    char gap40[0xE8];
    unsigned long flags;
    int mode;
};
void func_0023AE08(void *);
void func_001C9118(void *,int);
void func_00279708(struct Object *object)
{
    unsigned int tagged;
    func_0023AE08(object);
    object->mode=8;
    func_001C9118(object,1);
    tagged=object->taggedFlags;
    if((tagged^1)&1)
        *(int *)tagged|=8;
    else
        object->taggedFlags=tagged|8;
    object->flags&=~8UL;
}
