// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S;
struct PriorityContext {
    char prefix[0x84];
    struct S *source;
    char before_mode[0xA4 - 0x88];
    int mode;
};
struct PriorityKeyObject { char prefix[0xDC]; int key; };
struct S *func_001C7D60(struct S *source);
int func_0013CD00(int first, int second);

int func_00208A08(void *receiver, void *other, int priority)
{
    struct PriorityContext *context = receiver;
    int result = priority;
    if (context->mode == 1) {
        struct PriorityKeyObject *owner = (struct PriorityKeyObject *)func_001C7D60(context->source);
        if (owner && owner->key && ((struct PriorityKeyObject *)other)->key == owner->key)
            result = func_0013CD00(result, 3);
    }
    return result;
}
