// For a present stored owner, update its mask and then run the original receiver cleanup.
// Reference algorithm: src/hand/func_00132100.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0xA0]; void * owner; };
#include "owner_parent_link.h"
void func_00209428(struct S *object);
void func_002093E8(struct S *object)
{
    if(object->owner){func_001C7A00(object->owner,0,15);func_00209428(object);}
}
