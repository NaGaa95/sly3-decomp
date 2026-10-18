// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/vector_intrinsics.h"
struct SideEntry { short delta, padding; char *(*fn)(void *); };
struct SideTarget { unsigned char prefix[0xC]; SideEntry *table; };
struct SideSelf { unsigned char prefix[0x974]; SideTarget *target974; };
extern "C" int func_00139BB0(SideSelf *self);
extern "C" qword func_001C9428(void *source, void *destination, qword point);
extern "C" int func_00139F40(SideSelf *self)
{
    int flags = func_00139BB0(self);
    SideTarget *target = self->target974;
    qword local = func_001C9428(0, self, *(qword *)(target->table[36].fn((char *)target + target->table[36].delta) + 0x30));
    if(PackedVectorY(local) < 0.0f) flags |= 2;
    else flags |= 1;
    return flags;
}
