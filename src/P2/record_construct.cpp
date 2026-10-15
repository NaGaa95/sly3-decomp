// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Constructor helper chain; class identities remain provisional.
#include "record_construct.h"

extern "C" unsigned char D_0035D9A8[];
extern "C" unsigned char D_0035D988[];

extern "C" OBJECT_PREFIX *func_002BE7E0(OBJECT_PREFIX *p)
{
    p->pvTable = D_0035D9A8;
    return p;
}

extern "C" OBJECT_PREFIX *func_002BE748(OBJECT_PREFIX *p)
{
    func_002BE7E0(p);
    p->pvTable = D_0035D988;
    return p;
}

extern "C" OBJECT_WITH_PREFIX *func_002BE780(OBJECT_WITH_PREFIX *p)
{
    func_002BE748(&p->object);
    return p;
}

extern "C" OBJECT_WITH_NESTED_PREFIX *func_002BE7B0(OBJECT_WITH_NESTED_PREFIX *p)
{
    func_002BE780(&p->nested);
    return p;
}
