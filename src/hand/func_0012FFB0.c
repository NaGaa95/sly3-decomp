#include "actor_task_api.h"
struct ACTOR_TASK *func_0012FFB0(int kind,void *owner,void *channel,int mode,int identifier) {
    struct ACTOR_TASK *task=func_001306F0(kind);
    task->owner=owner;
    task->channel=channel;
    task->mode=mode;
    task->identifier=identifier;
    return task;
}
