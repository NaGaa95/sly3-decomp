// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "scene.h"
#include "mat.h"
#include "matrix_algorithms.h"
#include "actor_state_resource_api.h"
#include "resource_attachment_api.h"
#include "owner_parent_link.h"

struct ChannelView { char prefix[0xA0]; MATRIX3 *transform; };
struct PendingActorView {
    char prefix[0xC]; SCENE_VIRTUAL_ENTRY *table;
    void *parent;
    char reserved14[0x48 - 0x14];
    ChannelView *position, *rotation;
};
struct TransitionView {
    char prefix[0x84]; PendingActorView *active;
    char reserved88[0x94 - 0x88];
    void *positionTask, *middleTask, *rotationTask;
    PendingActorView *pending;
};
struct STATE_VIEW;
struct R;
extern "C" {
void func_00208B20(STATE_VIEW *state, int mode);
R *func_00130348(void *owner, void *channel, void *mode,
                float finish, qword point, qword finalPoint);
qword func_0028E910(SCENE_OBJECT *source, MATRIX4 *destination, qword point);
void func_0028EA00(MATRIX3 *output, SCENE_OBJECT *source,
                  MATRIX3 *destination, MATRIX4 *orientation);
extern float D_0036BB98;
extern qword D_00317560;
}

static inline MATRIX4 *ActorMatrix(SCENE_OBJECT *object)
{
    SCENE_VIRTUAL_ENTRY *entry = &object->vtable[36];
    return ((MATRIX4 *(*)(void *))entry->Simple)((char *)object + entry->delta);
}

extern "C" void func_00209490(void *context, void *payload)
{
    TransitionView *state = (TransitionView *)context;
    SCENE_OBJECT *source = (SCENE_OBJECT *)payload;
    MATRIX4 matrix;
    MATRIX3 temporary;
    if (!state->pending)
        return;
    func_00208B20((STATE_VIEW *)context, -1);
    func_001309D8(&state->positionTask);
    func_001309D8(&state->middleTask);
    func_001309D8(&state->rotationTask);
    if (source->owner) {
        SCENE_VIRTUAL_ENTRY *entry = &source->vtable[37];
        void *value = ((void *(*)(void *, MATRIX4 *))entry->Simple)
            ((char *)source + entry->delta, &matrix);
        PendingActorView *actor = state->pending;
        entry = &actor->table[10];
        ((OwnerParentCallback)entry->Simple)
            ((char *)actor + entry->delta, source->owner, value, 15);
    } else {
        func_001C7A00(state->pending, 0, 15);
    }
    ChannelView *channel = state->pending->position;
    qword point = func_0028E910(0, (MATRIX4 *)channel->transform,
                              ((qword *)ActorMatrix(source))[3]);
    state->positionTask = func_00130348(state->pending, channel, (void *)5,
                                        D_0036BB98 + 0.25f,
                                        point, D_00317560);
    channel = state->pending->rotation;
    func_0028EA00(&temporary, 0, channel->transform, ActorMatrix(source));
    *(MATRIX3 *)&matrix = temporary;
    state->rotationTask = func_00130078(state->pending, channel, 5, 8, 2,
                                       func_0011D3C0((MATRIX3 *)&matrix));
    state->active = state->pending;
    func_00208B20((STATE_VIEW *)context, 1);
    state->pending = 0;
}
