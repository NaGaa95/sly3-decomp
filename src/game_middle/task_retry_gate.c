// SLY3_CFLAGS: -Os -G0
struct OwnerView { unsigned char opaque000[0x3D8]; int key3D8; unsigned char opaque3DC[0x1080 - 0x3DC]; float retry1080; };
struct TaskView { unsigned char opaque00[0x10]; struct OwnerView *owner; unsigned char opaque14[0x1C]; int key30; unsigned char opaque34[8]; int result3C; };
extern float D_0036BB98;
int func_001A3BA8(struct OwnerView *owner, int key, int owner_key);
int func_001A4318(void *receiver)
{
    struct TaskView *task = (struct TaskView *)receiver;
    task->result3C = func_001A3BA8(task->owner, task->key30, task->owner->key3D8);
    if (task->result3C)
        return 1;
    if (task->owner->retry1080 < D_0036BB98)
        task->owner->retry1080 = D_0036BB98 + 0.25f;
    return 0;
}
