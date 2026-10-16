

// SLY3_CFLAGS: -Os -G0



#include "actor_task_clone_api.h"

void func_001A5CB0(struct ACTOR_TASK *p, const struct ACTOR_TASK *source, void *owner, void *channel) { func_0012F378(p, source, owner, channel); *(int *)((char *)p + 0x1C) = *(int *)(*(char **)((char *)p + 8) + 0xA8); }
