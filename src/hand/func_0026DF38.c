// Reset the inherited object and update its explicit stored owner state and mask.
// Reference algorithm: src/hand/func_00132100.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { void *owner; };
void func_00169E40(struct S *object);
#include "owner_parent_link.h"
void func_00166548(void *owner);
void func_0026DF38(struct S *object)
{
    func_00169E40(object);
    func_001C7A00(object->owner, 0, 15);
    func_00166548(object->owner);
}
