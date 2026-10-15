// Complete original inputs, full body and emitted sections independently reviewed.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ACTOR_VIEW {
    char unused00[0x130];
    int controller;
};
struct SCRIPT_CONTEXT {
    char unused00[0x28];
    struct ACTOR_VIEW *subject;
    char unused2C[0x3C - 0x2C];
    int active;
    unsigned int flags;
    int controller;
};
extern char D_00475480[];
extern int func_0013B500(void *actor, int type);
extern void func_001A93C8(void *game, int controller, unsigned int flags);
extern void func_001A9420(void *game, int controller, unsigned int flags);
extern void func_001A94A8(void *game, int controller);
extern void func_001A94F0(void *game, int controller);
void func_0022B290(struct SCRIPT_CONTEXT *context, int active, unsigned int flags) {
    if (!active) {
        if (!context->active) return;
    }
    else {
        if (context->active) {
            if (flags == context->flags) return;
            func_001A9420(D_00475480, context->controller, context->flags);
            func_001A94F0(D_00475480, context->controller);
        }
        if (context->subject && func_0013B500(context->subject, 0x31)) context->controller = context->subject->controller;
        else context->controller = -1;
        func_001A93C8(D_00475480, context->controller, flags);
        func_001A94A8(D_00475480, context->controller);
        context->active = active;
        context->flags = flags;
        return;
    }
    func_001A9420(D_00475480, context->controller, context->flags);
    func_001A94F0(D_00475480, context->controller);
    context->active = active;
    context->flags = flags;
}
