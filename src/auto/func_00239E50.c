// Return the selected scalar identifier from the actual request and record list.
#include "activation_selector_api.h"
struct RequestSelection { char prefix[0x24]; void *list; char padding[0x3C-0x28]; int selected; };
int func_00239E50(void *record)
{
    struct RequestSelection *request = record;
    return func_00239B80(request->list, request->selected);
}
