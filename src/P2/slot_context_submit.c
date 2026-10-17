// SLY3_CFLAGS: -Os -G0
struct Method { short adjustment, word2; void *function; };
struct MethodTable { unsigned char prefix[0x210]; struct Method accept; };
struct Provider { unsigned char prefix[0xC]; struct MethodTable *methods; };
struct Frame { unsigned char prefix[0x60]; struct Provider *provider; };
struct Link { unsigned char prefix[0xDC]; struct Frame *frame; };
struct ContextOwner { unsigned char prefix[0xA4]; int generation; };
struct Params { int first; int second; int third; int fourth; };
struct SlotContext {
    struct ContextOwner *owner;
    struct Link *link;
    unsigned char gap8[0x78 - 8];
    struct Params params;
    unsigned char gap88[0xC0 - 0x88];
    int generation;
};
void func_0023EDD0(void);
void func_0018B1E0(struct SlotContext *context);
void func_00206188(void *owner, void *slot, struct SlotContext *context, int a, int b, int c, void *d);
void func_00206C10(void *owner, struct SlotContext *context)
{
    unsigned int i;
    struct Provider *provider;
    func_0023EDD0();
    provider = context->link->frame->provider;
    if (((int (*)(void *))provider->methods->accept.function)((char *)provider + provider->methods->accept.adjustment)) {
        for (i = 0; i < 4; i++) {
            char *slot = (char *)owner + (i * 0x60 + 0x190);
            struct Params *params;
            if (context->generation != context->owner->generation)
                func_0018B1E0(context);
            params = &context->params;
            func_00206188(owner, slot, context, params->second, params->fourth, params->fourth, slot + 4);
        }
    }
}
