// Complete original inputs, full body and emitted sections independently reviewed.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "owned_record_list_api.h"
struct ACTOR_VIEW {
    char unused00[0x29C];
    struct ActorOwnedRecordList list;
};
struct COMMAND_VIEW {
    unsigned char kind;
};
struct SCRIPT_CONTEXT {
    char unused00[0x28];
    struct ACTOR_VIEW *subject;
    char unused2C[8];
    struct COMMAND_VIEW *command;
};
extern int func_0013B500(void *actor, int type);
void func_0022B890(struct SCRIPT_CONTEXT *context) {
    if (context->command) {
        switch (context->command->kind) {
            case 0x33: if (context->subject && func_0013B500(context->subject, 0x33)) func_00238568(&context->subject->list);
            break;
            case 0x34: if (context->subject && func_0013B500(context->subject, 0x33)) func_00238568(&context->subject->list);
            break;
        }
    }
}
