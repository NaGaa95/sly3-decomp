// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/scene.h"
#include "../P2/vector_intrinsics.h"
#include "../P2/matrix_algorithms.h"
#include "owner_parent_link.h"

union ControlChannelValue {
    qword packed;
    struct { int x, y; float z; int w; } components;
};
struct ControlChannel {
    char opaque00[0x9A];
    short mode;
    char opaque9C[4];
    MATRIX4 *transform;
    char opaqueA4[0xC0 - 0xA4];
    ControlChannelValue value;
};
struct ControlFrame { char opaque00[0x70]; qword position; };
struct ControlOwner {
    char opaque00[0x50];
    ControlFrame *frame;
    char opaque54[0x1194 - 0x54];
    ControlFrame *alternate;
};
struct ControlModeView {
    char opaque00[0xC]; SCENE_VIRTUAL_ENTRY *table;
    char opaque10[0x48 - 0x10];
    ControlChannel *position, *rotation;
    char opaque50[0x178 - 0x50];
    int state;
    float state_time;
    char opaque180[8];
    int enabled;
    ControlOwner *owner;
};
union ControlOffset { float lanes[4]; qword packed; };
static const ControlOffset control_offset = { {0.0f, 0.0f, -50.0f, 0.0f} };

extern "C" {
void func_0028F068(void *receiver, ControlChannel *channel, int mode);
void func_0023EBF8(void *receiver, int mode);
void func_0023EC98(void *receiver, int mode);
void func_0023FCD8(void *receiver, int mode);
void func_0015B0E8(void *game);
void func_0011CCF8(const MATRIX4 *input, MATRIX3 *optional, MATRIX3 *output);
void func_0028EA00(MATRIX3 *output, SCENE_OBJECT *source, MATRIX3 *destination, MATRIX4 *orientation);
qword func_0028E910(SCENE_OBJECT *source, MATRIX4 *destination, qword point);
extern unsigned char D_00475480[];
extern qword D_00317560;
struct ControlModeClock { float now; };
extern ControlModeClock D_0036BB98;
}

static inline qword ControlAdd(qword first, qword second)
{
    qword result;
    asm("vadd.xyzw %0,%1,%2" : "=j"(result) : "j"(first), "j"(second));
    return result;
}

static inline MATRIX4 *ControlMatrix(ControlModeView *receiver)
{
    SCENE_VIRTUAL_ENTRY *entry = &receiver->table[36];
    return (MATRIX4 *)entry->Query((char *)receiver + entry->delta);
}

static inline void ControlMessage(ControlModeView *receiver, int message)
{
    SCENE_VIRTUAL_ENTRY *entry = &receiver->table[3];
    ((void (*)(void *, int, int, int, void **, void *))entry->Simple)
        ((char *)receiver + entry->delta, message, 0, 0, 0, 0);
}

extern "C" void func_001A1A28(ControlModeView *receiver, int mode)
{
    if (receiver->state == mode)
        return;
    if (receiver->state == 2) {
        if (receiver->enabled) {
            func_001C7A00(receiver, 0, 15);
            func_0028F068(receiver, receiver->position, 1);
            receiver->position->mode = 0;
            func_0028F068(receiver, receiver->rotation, 1);
            receiver->rotation->mode = 0;
            SCENE_VIRTUAL_ENTRY *entry = &receiver->table[40];
            ((void (*)(void *, qword))entry->Simple)
                ((char *)receiver + entry->delta, D_00317560);
            func_0023EBF8(receiver, 0);
            func_0023EC98(receiver, 0);
            func_0023FCD8(receiver, 0);
        }
        ControlMessage(receiver, 6);
        func_0015B0E8(D_00475480);
        receiver->owner = 0;
    }
    if (mode == 2) {
        if (receiver->enabled) {
            MATRIX3 matrix, temporary;
            func_0023EBF8(receiver, 1);
            func_0023EC98(receiver, 1);
            ControlFrame *frame = receiver->owner->alternate;
            if (!frame)
                frame = receiver->owner->frame;
            SCENE_VIRTUAL_ENTRY *entry = &receiver->table[10];
            ((OwnerParentCallback)entry->Simple)
                ((char *)receiver + entry->delta, receiver->owner, frame, 3);
            func_0011CCF8(ControlMatrix(receiver), 0, &matrix);
            func_0028EA00(&temporary, 0, (MATRIX3 *)receiver->rotation->transform, (MATRIX4 *)&matrix);
            matrix = temporary;
            qword rotation = func_0011D3C0(&matrix);
            func_0028F068(receiver, receiver->rotation, 8);
            ControlChannelValue *value = &receiver->rotation->value;
            value->components.x = 0;
            value->components.z = PackedVectorZ(rotation);
            value->components.y = 0;
            receiver->rotation->mode = mode;
            qword position = func_0028E910(0, receiver->position->transform,
                ControlAdd(frame->position, control_offset.packed));
            func_0028F068(receiver, receiver->position, 8);
            receiver->position->value.packed = position;
            receiver->position->mode = mode;
            func_0023FCD8(receiver, 1);
        }
        ControlMessage(receiver, 5);
    }
    receiver->state = mode;
    receiver->state_time = D_0036BB98.now;
}
