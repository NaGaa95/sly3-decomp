// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/vector_intrinsics.h"

struct AdjustMethod { short adjustment, word2; void *function; };
struct AdjustTable { unsigned char prefix[0x120]; AdjustMethod matrix; };
struct AdjustObject { unsigned char prefix[0xC]; AdjustTable *methods; };
struct AdjustMatrix { unsigned char prefix[0x30]; qword position; };
struct AdjustCommand {
    unsigned char prefix0[8];
    float height;
    unsigned char gapC[0x34 - 0xC];
    float depth;
    unsigned char gap38[0x6C - 0x38];
    int flags;
};
struct AdjustActor {
    unsigned char prefix[0x50C];
    int word50C;
    unsigned char gap510[0x1014 - 0x510];
    int word1014;
    unsigned char gap1018[0x19E0 - 0x1018];
    int state;
    unsigned char gap19E4[0x19F4 - 0x19E4];
    AdjustObject *object;
};
extern "C" {
extern float D_0036BB98;
void func_00153D40(void *actor, void *command);

static inline float ObjectHeight(AdjustObject *object)
{
    AdjustMethod *method = &object->methods->matrix;
    return PackedVectorZ(((AdjustMatrix *(*)(void *))method->function)((char *)object + method->adjustment)->position);
}

void func_001ABA80(AdjustActor *actor, AdjustCommand *command)
{
    if (actor->state != 0 && actor->state != 0xE) {
        if (actor->word50C && actor->word1014 != 1)
            *(float *)((char *)actor + 0x1B0C) = D_0036BB98;
    }
    func_00153D40(actor, command);
    switch (actor->state) {
    case 4:
        command->height = ObjectHeight(actor->object) + -175.0f;
        command->flags &= ~4;
        break;
    case 0x11:
        command->height = ObjectHeight(actor->object) + -100.0f;
        command->flags &= ~4;
        break;
    case 0x13:
        command->depth = command->depth - 75.0f;
        break;
    }
    switch (actor->state) {
    case 4:
    case 6:
    case 7:
        command->flags |= 1;
        break;
    }
}
}
