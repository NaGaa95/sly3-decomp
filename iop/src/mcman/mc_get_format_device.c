#include "mc_device_view.h"

int McGetFormat(int port, int slot)
{
    return mcman_device_infos[port][slot].cardFormat;
}
