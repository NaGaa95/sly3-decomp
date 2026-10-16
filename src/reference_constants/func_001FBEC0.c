// SLY3_CFLAGS: -Os -G0
#include "resource_selected_child_pointer_api.h"
struct ResourceChildTable { unsigned int word0; void **children; };
struct ResourceChildView {
    char unaccessed[0xD0];
    struct ResourceChildTable *table;
    unsigned int wordD4;
    void *selected_entry;
};
int func_001FB5D8(struct ResourceChildView *resource,void *entry);
void *func_001FBEC0(void *receiver)
{
    struct ResourceChildView *resource=(struct ResourceChildView *)receiver;
    int index;
    if(!resource->selected_entry)
        return 0;
    index=func_001FB5D8(resource,resource->selected_entry);
    return resource->table->children[index];
}
