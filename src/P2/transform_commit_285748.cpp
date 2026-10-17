// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "mat.h"
struct CommitTransform {
    MATRIX4 matrix;
    char pad40[0x94-0x40];
    int busy;
    char pad98[0xA4-0x98];
    int generation;
};
struct CommitObject {
    char prefix[0x40];
    int count;
    CommitTransform *local;
    char pad48[0x3E0-0x48];
    MATRIX4 world;
};
struct CommitGlobals { char prefix[0x44F4]; int generation; };
extern "C" CommitGlobals D_00475480;
extern "C" void func_001F3C80(void *);
extern "C" void func_00286360(void *,int);
extern "C" void func_00285748(CommitObject *object)
{
    func_001F3C80(object);
    func_00286360(object,-1);
    if(object->count>0) {
        CommitTransform *local=object->local;
        if(!local->busy) {
            local->matrix=object->world;
            int generation=++D_00475480.generation;
            object->local->generation=generation;
        }
    }
}
