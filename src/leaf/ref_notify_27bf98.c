// SLY3_CFLAGS: -Os -G0
struct Method { short adjustment, word2; void *function; };
struct MethodTable { unsigned char prefix[0x210]; struct Method accept; };
struct Provider { unsigned char prefix[0xC]; struct MethodTable *methods; };
struct Frame { unsigned char prefix[0x60]; struct Provider *provider; };
struct Link { unsigned char prefix[0xDC]; struct Frame *frame; };
struct ContextOwner { unsigned char prefix[0xA4]; int generation; };
struct Params { int first; int second; int third; int fourth; };
union Flags { unsigned long all; struct { unsigned int low; int key; } half; };
struct Context {
    struct ContextOwner *owner;
    struct Link *link;
    unsigned char gap8[0x18 - 8];
    union Flags flags;
    unsigned char gap20[0x78 - 0x20];
    struct Params params;
    unsigned char gap88[0xC0 - 0x88];
    int generation;
};
struct Ref { unsigned char prefix[0x18]; union Flags flags; };
struct Owner {
    unsigned char prefix[0x344];
    struct Ref *refs[2];
    unsigned char gap34C[0x354 - 0x34C];
    struct Ref *third;
    unsigned char tail[4];
};
extern unsigned char D_00475480[];
void func_0023EDD0(void);
void func_0018B1E0(struct Context *context);
int func_00240E10(void *object, int key);
void func_001CD858(void *pool, struct Context *context, struct Ref *ref, int a, int b, void *tail);
void func_001CC790(void *pool, struct Ref *ref, struct Context *context, int second, int fourth, int fourthAgain, void *tail);
void func_0027B588(struct Owner *owner, void *slot, struct Context *context, int second, int fourth, int fourthAgain, void *tail);
void func_0027BF98(struct Owner *owner, struct Context *context, int unused2, int unused3, int unused4, void *extra)
{
    struct Params *params;
    unsigned int i;
    struct Provider *provider;
    func_0023EDD0();
    if (context->generation != context->owner->generation)
        func_0018B1E0(context);
    params = &context->params;
    {
        struct Ref *first = owner->refs[0];
        if ((first && first->flags.half.key) || (owner->refs[1] && owner->refs[1]->flags.half.key)) {
            int key = (first && first->flags.half.key) ? first->flags.half.key : owner->refs[1]->flags.half.key;
            if (func_00240E10(*(void **)((char *)context + 4), key)) {
                for (i = 0; i < 2; i++) {
                    struct Ref *ref = owner->refs[i];
                    if (ref && ref->flags.half.key) {
                        if (context->flags.all & 0x20000)
                            func_001CD858(D_00475480, context, ref, 0, 0, extra);
                        else
                            func_001CC790(D_00475480, ref, context, params->second, params->fourth, params->fourth, extra);
                    }
                }
            }
        }
    }
    if (owner->third && !(owner->third->flags.all & 0x80000)) {
        if (context->flags.all & 0x20000)
            func_001CD858(D_00475480, context, owner->third, 0, 0, owner->tail);
        else
            func_001CC790(D_00475480, owner->third, context, params->second, params->fourth, params->fourth, owner->tail);
    }
    provider = context->link->frame->provider;
    if (((int (*)(void *))provider->methods->accept.function)((char *)provider + provider->methods->accept.adjustment)) {
        for (i = 0; i < 4; i++) {
            char *slot = (char *)owner + (i * 0x60 + 0x190);
            func_0027B588(owner, slot, context, params->second, params->fourth, params->fourth, slot + 4);
        }
    }
}
