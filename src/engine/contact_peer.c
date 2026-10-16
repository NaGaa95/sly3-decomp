// SLY3_CFLAGS: -Os -G0
#include "contact_notify_supplied_side_api.h"
typedef struct ContactPeer {
    char prefix[0x1D0];
    unsigned int word1D0;
} ContactPeer;
typedef struct ContactPeerReceiver {
    char prefix[0x190];
    int enabled;
    char pad194[0x1D0 - 0x194];
    unsigned int word1D0;
    char pad1D4[0x3F8 - 0x1D4];
    ContactPeer *selected;
} ContactPeerReceiver;
typedef struct ContactPeerSide {
    char prefix[8];
    ContactPeer *object;
    char unaccessed[0x40 - 0xC];
} ContactPeerSide;
int func_0013B500(void *object, int identifier);
void func_0019BB00(void *receiver, int mode, void *peer);

void func_0019D9B0(ContactPeerReceiver *receiver, ContactPeerSide *sides, int side)
{
    func_0019B6B0(receiver, sides, side);
    if (receiver->enabled) {
        ContactPeerSide *opposite = &sides[1 - side];
        ContactPeer *peer = opposite->object;
        if (func_0013B500(peer, 0x49) && !func_0013B500(peer, 0x4C) &&
            peer->word1D0 != receiver->word1D0) {
            receiver->selected = peer;
            func_0019BB00(receiver, 1, peer);
        }
    }
}
