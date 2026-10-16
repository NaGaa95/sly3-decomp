// SLY3_CFLAGS: -Os -G0
#include "contact_notify_supplied_side_api.h"
struct ContactGateSide {
    char prefix[12];
    void *object;
    char unused10[48];
};
struct ContactGateEvent {
    struct ContactGateSide sides[2];
    char unused80[24];
    float amount98;
};
struct ContactGateOwner {
    char prefix[0x1FC];
    int gate;
};
int func_0013B500(void *receiver, int identifier);
void func_0019BB00(void *receiver, int mode, void *peer);
void func_0019CCB0(struct ContactGateOwner *owner, struct ContactGateEvent *event, int side)
{
    struct ContactGateSide *opposite;
    void *peer;
    func_0019B6B0(owner, event, side);
    opposite=&event->sides[1-side];
    peer=opposite->object;
    if (func_0013B500(peer, 0x49)||!owner->gate)
        func_0019BB00(owner, 1, peer);
    if (owner->gate)
        event->amount98=1.0f;
}
