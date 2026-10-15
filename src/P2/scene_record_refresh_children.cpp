// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"

extern "C" void func_0023C878(void *);
extern "C" int func_0013B500(SCENE_OBJECT *, int);
extern "C" void func_002BE8D0(void *, int);

struct SceneRefreshChildrenScope {
    ~SceneRefreshChildrenScope() { func_002BE8D0(this, 2); }
};
typedef char CheckRefreshChildrenScope1[sizeof(SceneRefreshChildrenScope) == 1 ? 1 : -1];

extern "C" void func_0023C8F8(SCENE_OBJECT *object)
{
    SceneRefreshChildrenScope scope;
    func_0023C878(object);
    for (SCENE_OBJECT *child = object->children.first;
         child != object->anchor; child = child->previous) {
        if (func_0013B500(child, 0x2F)) func_0023C8F8(child);
    }
}
