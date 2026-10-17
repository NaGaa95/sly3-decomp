// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "mat.h"
struct CommitEntry {
    short delta,pad;
    union {
        void (*Simple)(void *);
        void (*Argument)(void *,int);
    };
};
struct CommitTransform {
    MATRIX4 matrix;
    char pad40[0x94-0x40];
    int busy;
    char pad98[0xA4-0x98];
    int generation;
};
struct CommitObject {
    char prefix[0xC];
    CommitEntry *vtable;
    char pad10[0x40-0x10];
    int count;
    CommitTransform *local;
    char pad48[0x190-0x48];
    MATRIX4 matrix;
};
struct CommitGlobals { char prefix[0x44F4]; int generation; };
extern "C" CommitGlobals D_00475480;
extern "C" void func_001FCB20(void *);
extern "C" void func_00276F88(CommitObject *object)
{
    func_001FCB20(object);
    CommitEntry *argumentEntry=&object->vtable[80];
    argumentEntry->Argument((char *)object+argumentEntry->delta,-1);
    CommitEntry *simpleEntry=&object->vtable[9];
    simpleEntry->Simple((char *)object+simpleEntry->delta);
    if(object->count>0) {
        CommitTransform *local=object->local;
        if(!local->busy) {
            local->matrix=object->matrix;
            int generation=++D_00475480.generation;
            object->local->generation=generation;
        }
    }
}
