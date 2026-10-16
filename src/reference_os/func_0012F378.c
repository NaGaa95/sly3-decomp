// SLY3_CFLAGS: -Os -G0
#include "actor_task_clone_api.h"
typedef struct G { int pad[3]; unsigned int cb; } G;
extern G D_004799AC;
void func_001D2898(void *dst, void *src, unsigned int cb);

void func_0012F378(struct ACTOR_TASK *t, const struct ACTOR_TASK *src, void *b, void *c)
{
    t->kind = src->kind;
    t->mode = src->mode;
    t->identifier = src->identifier;
    t->owner = b;
    t->channel = c;
    func_001D2898((char *)t + 0x1C, (char *)src + 0x1C, D_004799AC.cb - 0x1C);
}
