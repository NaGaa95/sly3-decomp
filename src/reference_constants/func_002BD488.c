// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31
// Shared observed Sly 3 layouts and coherent cohort helper declarations.
#include "runtime_geometry_access.h"

void func_002BD488(RuntimeOwner *owner, void *stream)
{
    struct ALLOCREQ request;
    request.cb = 0x100;
    request.cbAlign = 0x10;
    func_00177488((struct S *)(owner->geometry = func_001D2470(&request)));
    func_0028FDE0(owner, stream);
    if (owner->geometry->loader_kind == 3)
        func_001775B8(owner->geometry->loader_detail, stream);
    func_002BD398((struct X *)owner, stream);
}
