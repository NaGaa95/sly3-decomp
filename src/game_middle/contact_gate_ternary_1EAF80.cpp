// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/scene.h"

struct PermissionRoot {
    char prefix[0x360];
    int permission;
};

extern "C" {
int func_001C8F20(SCENE_OBJECT *object, void *ancestor);
int func_0013B500(void *object, int kind);

int func_001EAF80(void *ancestor, SCENE_OBJECT *object)
{
    int inherited = object->flags.fields.inherited;
    if (!inherited)
        return 0;
    if (func_001C8F20(object, ancestor))
        return 0;
    SCENE_OBJECT *root = object->handle->object;
    if (func_0013B500(root, 0x3A) ? ((PermissionRoot *)root)->permission : func_0013B500(root, 0x66))
        return 0;
    if (object->owner && func_0013B500(object->owner, 0x66))
        return 0;
    return 1;
}
}
