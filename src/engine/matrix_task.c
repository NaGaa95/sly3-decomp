// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "actor_task_api.h"
struct MatrixTaskRows { EE_ATTACHMENT_QWORD row[4]; } __attribute__((aligned(16)));
struct MatrixTask {
    struct ACTOR_TASK base;
    unsigned char unused1C[4];
    struct MatrixTaskRows matrix;
};
struct MatrixTaskRuntime {
    struct MatrixTaskRows matrix;
    unsigned char unused40[0x80];
    EE_ATTACHMENT_QWORD value;
    EE_ATTACHMENT_QWORD derivative;
};
extern EE_ATTACHMENT_QWORD D_00317560, D_00317570;
void func_0028B188(void *, struct MatrixTaskRuntime *);
void func_0012F600(struct MatrixTask *task)
{
    struct MatrixTaskRuntime *runtime = task->base.channel;
    runtime->value = D_00317570;
    ((struct MatrixTaskRuntime *)task->base.channel)->derivative = D_00317560;
    ((struct MatrixTaskRuntime *)task->base.channel)->matrix = task->matrix;
    func_0028B188(task->base.owner, task->base.channel);
}
void *func_00130100(void *owner, void *channel, int mode, int identifier,
                   const struct MatrixTaskRows *matrix)
{
    struct MatrixTask *task = (struct MatrixTask *)func_0012FFB0(11, owner, channel, mode, identifier);
    task->matrix = *matrix;
    func_0028ECE0(owner, channel, &task->base);
    return task;
}
