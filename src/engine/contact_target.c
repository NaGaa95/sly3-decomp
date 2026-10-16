// SLY3_CFLAGS: -Os -G0
#include "contact_notify_supplied_side_api.h"
struct ContactTargetSide {
    char prefix[0xC];
    void *object;
    char unused10[0x30];
};
struct ContactTargetEvent {
    struct ContactTargetSide sides[2];
    char unused80[0x14];
    float scalar94, scalar98;
};
struct ContactTargetOwner {
    char prefix[0x190];
    unsigned int enabled;
};
typedef char CheckContactTargetSide64[sizeof(struct ContactTargetSide)==64?1:-1];
int func_0013B500(void *object, int type);
void func_0019BB00(void *owner, int enabled, void *source);
void func_0019F1B8(struct ContactTargetOwner *owner, struct ContactTargetEvent *event, int side)
{
    func_0019B6B0(owner, event, side);
    if (owner->enabled) {
        struct ContactTargetSide *other=&event->sides[1-side];
        void *object=other->object;
        if (func_0013B500(object, 0x49))
            func_0019BB00(owner, 1, object);
    }
}
