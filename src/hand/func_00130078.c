#include "actor_task_api.h"
struct PACKED_ACTOR_TASK {
    struct ACTOR_TASK base;
    int flags;
    EE_ATTACHMENT_QWORD value;
};
void *func_00130078(void *owner,void *channel,int mode,int identifier,int flags,EE_ATTACHMENT_QWORD value) {
    struct PACKED_ACTOR_TASK *task=(struct PACKED_ACTOR_TASK *)func_0012FFB0(1,owner,channel,mode,identifier);
    task->flags=flags;
    task->value=value;
    func_0028ECE0(owner,channel,(struct ACTOR_TASK *)task);
    return task;
}
