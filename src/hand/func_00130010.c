#include "actor_task_api.h"
void *func_00130010(void *owner,void *channel,int mode) {
    struct ACTOR_TASK *task=func_0012FFB0(5,owner,channel,mode,-1);
    func_0028ECE0(owner,channel,task);
    return task;
}
