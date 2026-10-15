// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "animation_ensure_api.h"
enum SEEK { SEEK_ABSOLUTE = 0, SEEK_RELATIVE = 1, SEEK_FROM_END = 2 };
void EnsureAseg(ASEG *animation, ALO *owner, SEEK seek, float time,
                float rate, int flags, ASEGA **output)
{
    ASEGA *runtime;
    if (!output)
        output = &runtime;
    runtime = func_00137448(animation,owner);
    if (runtime)
        *output = runtime;
    else
        func_00136908(animation,owner,0.0f,1.0f,flags,output);
    func_00137D08(static_cast<SeekRuntime *>(static_cast<void *>(*output)),
                   seek,time,rate,0);
}
