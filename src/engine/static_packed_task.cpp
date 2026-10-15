// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "actor_task_api.h"
struct StaticPackedTask {
    struct ACTOR_TASK base;
    int flags;
    EE_ATTACHMENT_QWORD value;
};
struct StaticPackedRuntime {
    unsigned char prefix[0x9A];
    unsigned short samples;
    unsigned char unused9C[0x24];
    EE_ATTACHMENT_QWORD value, derivative;
};
extern EE_ATTACHMENT_QWORD D_00317560;
void func_0028B188(void *, struct StaticPackedRuntime *);
void func_0012F478(struct StaticPackedTask *task)
{
    struct StaticPackedRuntime *runtime = (struct StaticPackedRuntime *)task->base.channel;
    runtime->value = task->value;
    ((struct StaticPackedRuntime *)task->base.channel)->derivative = D_00317560;
    ((struct StaticPackedRuntime *)task->base.channel)->samples = (unsigned short)task->flags;
    func_0028B188(task->base.owner, (struct StaticPackedRuntime *)task->base.channel);
}
struct XYZ { float x, y, z; };
struct StaticPackedXYZSlot { XYZ xyz; unsigned char residue[4]; } __attribute__((aligned(16)));
static __inline__ void ClearXYZ(StaticPackedXYZSlot *slot)
{
    slot->xyz.x = slot->xyz.y = slot->xyz.z = 0;
}
void func_0012F4C8(struct StaticPackedTask *task, EE_ATTACHMENT_QWORD *value, StaticPackedXYZSlot *derivative)
{
    if (value)
        *value = task->value;
    if (derivative)
        ClearXYZ(derivative);
}
}
