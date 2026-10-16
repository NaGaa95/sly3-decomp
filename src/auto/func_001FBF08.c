#include "actor_resource_lookup_api.h"
#include "m2c_prelude.h"
#include "resource_selected_child_pointer_api.h"
void *func_001FBF08(void *resource)
{
    void *child=func_001FBEC0(resource);
    if(!child)
        child=func_001FBE30(resource,1);
    return child;
}
