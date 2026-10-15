// SLY3_CFLAGS: -Os -G0
#include "animation_ensure_api.h"
struct ALO;
struct ASEGA {
    char before_owner[0x18];
    struct ALO *owner;
    char before_next[0x2C - 0x1C];
    struct ASEGA *next;
};
struct ASEG {
    char prefix[0x40];
    struct ASEGA *first;
};
struct AnimationSearchScope { unsigned char unused_storage[16]; };
void func_002BBEC8(void *unused_scope,int flags);
struct ASEGA *func_00137448(struct ASEG *animation,
                                      struct ALO *owner)
{
    struct AnimationSearchScope scope;
    struct ASEGA *runtime;
    for (runtime = animation->first; runtime; runtime = runtime->next) {
        if (runtime->owner == owner) {
            func_002BBEC8(&scope,2);
            return runtime;
        }
    }
    func_002BBEC8(&scope,2);
    return 0;
}
