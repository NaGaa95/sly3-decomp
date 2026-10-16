// SLY3_CFLAGS: -Os -G0
#include "actor_task_clone_api.h"
struct TaskCloneMethod {
    short delta, reserved;
    void (*call)(struct ACTOR_TASK *,const struct ACTOR_TASK *,void *,void *);
};
struct ACTOR_TASK *func_00130968(const struct ACTOR_TASK *source, void *owner, void *channel)
{
    struct ACTOR_TASK *task = func_001306F0(source->kind);
    struct TaskCloneMethod *method = &((struct TaskCloneMethod *)task->dispatch)[6];
    method->call((struct ACTOR_TASK *)((unsigned char *)task + method->delta), source, owner, channel);
    return task;
}
