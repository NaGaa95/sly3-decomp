// Bind a target position to the subject links and clear their three motion components.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int QWORD __attribute__((mode(TI)));
union POSITION {
    QWORD packed;
    float component[4];
};
struct V3 {
    float x,y,z;
};
struct POSITION_LINK {
    union POSITION position;
    struct V3 motion;
    char unused1C[0x64 - 0x1C];
    struct POSITION_LINK *next;
};
struct ACTOR_VIEW {
    char unused00[0x158];
    struct POSITION_LINK *head;
    char unused15C[0x1158 - 0x15C];
    float height;
};
struct SCRIPT_CONTEXT {
    char unused00[0x28];
    struct ACTOR_VIEW *subject;
    char unused2C[0x7C - 0x2C];
    void *target;
};
extern int func_0013B500(void *actor, int type);
extern void func_00153EA0(void *actor, int enabled);
extern void func_0022AEC8(void *context, void *target, union POSITION *outputPosition, float *outputHeading);
void func_0022B150(struct SCRIPT_CONTEXT *context, void *target) {
    struct ACTOR_VIEW *actor;
    if (context->subject && func_0013B500(context->subject, 0x33)) actor = context->subject;
    else actor = 0;
    if (context->target) {
        if (actor) func_00153EA0(actor, 0);
        context->target = 0;
    }
    if (!target) return;
    if (actor) {
        union POSITION position;
        struct POSITION_LINK *link;
        // The original helper can leave output unchanged on some target paths.
        func_0022AEC8(context, target, &position, 0);
        position.component[2] += actor->height;
        for (link = actor->head; link; link = link->next) {
            struct V3 *motion = &link->motion;
            // The earlier disable helper can write all four motion words; this loop clears xyz only.
            link->position.packed = position.packed;
            motion->z = 0.0f;
            motion->y = 0.0f;
            link->motion.x = 0.0f;
        }
        func_00153EA0(actor, 1);
    }
    context->target = target;
}
