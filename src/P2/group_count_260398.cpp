// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct Subject { unsigned char prefix[0x44]; int mode; };
struct Slot { Subject *subject; int other; };
struct Group {
    unsigned char prefix[0x120];
    int secondCount;
    unsigned char gap124[4];
    Slot second[1];
};
struct GroupView {
    unsigned char prefix[0x1A4];
    int firstCount;
    unsigned char gap1A8[4];
    Slot first[1];
};
extern "C" {
extern char D_00327ED0[];
void func_00261250(void *group);
int func_00188A38(Subject *subject);
int func_00260758(void *group, int key);
int func_00271530(char *output, unsigned int capacity, const char *format, ...);
}
extern "C" void func_00260398(Group *group)
{
    GroupView *view = (GroupView *)group;
    int active = 0;
    int firstActive = 0;
    int i = 0;
    int fixed = 0;
    func_00261250(group);
    while (i < view->firstCount) {
        Slot *slot = &view->first[i];
        Subject *subject = slot->subject;
        if (subject) {
            if (subject->mode == 1)
                fixed++;
            else if (func_00188A38(subject)) {
                active++;
                firstActive++;
            }
        }
        i++;
    }
    for (i = 0; i < group->secondCount; i++) {
        Slot *slot = &group->second[i];
        Subject *subject = slot->subject;
        if (subject) {
            if (subject->mode == 1)
                fixed++;
            else if (func_00188A38(subject))
                active++;
        }
    }
    if (func_00260758(group, 0x37B)) {
        func_00271530((char *)group + 0x2A8, 4, D_00327ED0, firstActive);
        func_00271530((char *)group + 0x2AC, 4, D_00327ED0, view->firstCount);
        func_00271530((char *)group + 0x2B0, 4, D_00327ED0, view->firstCount - firstActive);
    }
    if (active == view->firstCount + group->secondCount) {
        CallScene((SCENE_OBJECT *)group, 54);
    } else if (fixed == 0) {
        CallScene((SCENE_OBJECT *)group, 54);
    } else if (fixed > 0) {
        CallScene((SCENE_OBJECT *)group, 56);
    }
}
