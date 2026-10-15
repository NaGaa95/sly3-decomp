// Retain an actual state object through the six-input constructor helper.
#include "activation_selector_api.h"
void func_00239808(void *resource, void *receiver, int identifier, int mode, int mask, void **output);
void *func_002399C8(void *resource, void *receiver, int identifier, int mode)
{
    void *retained;
    func_00239808(resource, receiver, identifier, mode, 4, &retained);
    return retained;
}
