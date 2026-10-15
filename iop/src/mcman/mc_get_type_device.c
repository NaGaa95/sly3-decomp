#include "mc_device_view.h"

int McGetMcType(int port, int slot)
{
    return mcman_device_infos[port][slot].cardType;
}
