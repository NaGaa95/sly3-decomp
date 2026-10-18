// SLY3_CFLAGS: -Os -G0
#include "activation_selector_api.h"
struct PanelChild { char prefix[0x130]; int mode; };
struct PanelModeOwner {
    char prefix[0x130]; int key; void *selectorOwner;
    char gap138[0x190-0x138]; int mode; float changed;
    int childMode; float childChanged; void *list;
    int count; struct PanelChild *children[7]; int index;
    int flag1C8, flag1CC, pending;
    char request[0x10];
};
struct PanelModeClock { float now, step; };
extern struct PanelModeClock D_0036BB98;
extern char D_00475480[];
void func_00171670(void *owner, int mode);
void func_00171740(void *owner);
void func_00170F60(void *child, int mode);
void func_001F4B00(void *world, int key, void *owner);

void func_00171538(struct PanelModeOwner *owner, int mode)
{
    int i;
    if(owner->mode == mode)
        return;
    if(owner->mode == 2) {
        func_00171670(owner, -1);
        if(owner->key != -1)
            func_001F4B00(D_00475480, owner->key, owner->list);
    }
    owner->mode = mode;
    owner->changed = D_0036BB98.now;
    switch(mode) {
    case 0:
        func_00171740(owner);
        break;
    case 1:
        for(i=0;i<owner->count;i++)
            func_00170F60(owner->children[i], 2);
        break;
    case 2:
        func_001F4B00(D_00475480, 0, owner);
        func_001A99D0(owner->request, owner->selectorOwner);
        owner->index = 0;
        func_00171670(owner, 2);
        owner->pending = 0;
        break;
    case 3:
        owner->pending = 1;
        break;
    }
}
