// SLY3_CFLAGS: -Os -G0
#include "matrix_xy_resource_api.h"
struct PanelSlot { void *resource; int word4; int word8; };
struct Panels { unsigned char prefix[0x42D8]; struct PanelSlot slots[4]; };
extern int D_00327720[4];
extern unsigned char D_00475480[];
void *func_0017E1B8(void *game, int flags, int key_word, void *owner);
void *func_00292034(void *destination, int value, int bytes);
void func_0025CA70(struct Panels *panels)
{
    struct MatrixXYValue identity;
    int index;
    func_00292034(&identity, 0, sizeof(identity));
    identity.value[3] = 1.0f;
    identity.value[0] = 1.0f;
    for (index = 0; index < 4; index++) {
        struct PanelSlot *slot = &panels->slots[index];
        void *resource = func_0017E1B8(D_00475480, 0x405, D_00327720[index], 0);
        if (resource) {
            func_00262848(resource, &identity);
            slot->resource = resource;
        }
    }
}
