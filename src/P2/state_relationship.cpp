// State transitions, linked-object updates and action/event notifications.
// This prefix view does not assign an original concrete class name or full size.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
class RelationshipBase {
    public: int a, b, c;
    virtual void V1();
    virtual void V2();
    virtual void Msg(int msgid, int a, int c, void **apv, int d);
    virtual void V4(int msgid, void *pv);
};
struct ACTION;
struct NOTIFY;
class RelationshipObject : public RelationshipBase {
    public: int f10, f14, f18;
    char pad1C[0x44 - 0x1C];
    int state44;
    float time48;
    char pad4C[0x54 - 0x4C];
    RelationshipObject *partner54;
    int counter58;
    char pad5C[0x60 - 0x5C];
    int word60, word64;
    char pad68[0x6C - 0x68];
    RelationshipObject *link6C;
    char pad70[0x7C - 0x70];
    RelationshipObject *reciprocal7C;
    char pad80[0x98 - 0x80];
    int actionCount98;
    ACTION *actions9C;
    int notificationCountA0;
    NOTIFY *notificationsA4;
    char padA8[0xFC - 0xA8];
    int kindFC;
};
typedef char CheckStateViewSize[(sizeof(RelationshipObject) == 256) ? 1 : -1];
struct DL {
    void *pvFirst;
    void *pvLast;
    int ibDle;
};
struct CLOCK {
    float t;
};
extern CLOCK D_0036BB98;
extern DL D_004794B8;
extern char D_0036C700[];
extern "C" int func_001880F0(RelationshipObject *p);
extern "C" void func_001854C8(void *pv, int n, RelationshipObject *p);
extern "C" void func_0011B028(DL *pdl, void *pv);
extern "C" void func_0011AF60(DL *pdl, void *pv);
extern "C" void func_00185A70(RelationshipObject *p, int n, int c, ACTION *actions);
extern "C" void func_00185DB0(RelationshipObject *p, int n, int c, NOTIFY *notifications, int kind);
extern "C" void func_00188DE0(RelationshipObject *p);
#include "relationship_lifecycle_api.h"
extern "C" void func_00188620(RelationshipObject *p);
extern "C" void func_0018A3E8(RelationshipObject *p, int n) {
    if (p->state44 == n) return;
    if (func_001880F0(p)) {
        func_001854C8(D_0036C700, 0x2A, p);
        p->Msg(0x19, 0, 0, 0, 0);
    }
    if (p->state44 == 1) func_0011B028(&D_004794B8, p);
    if (func_001880F0(p)) {
        func_00185A70(p, n, p->actionCount98, p->actions9C);
        func_00185DB0(p, n, p->notificationCountA0, p->notificationsA4, p->kindFC);
    }
    switch (n) {
        case 0: if (p->kindFC == 4) {
            p->partner54 = 0;
            p->counter58 = 0;
            if (p->link6C && p->link6C->partner54 == p) p->link6C->reciprocal7C = 0;
        }
        break;
        case 1: func_0011AF60(&D_004794B8, p);
        break;
        case 2: if (p->kindFC == 0 || p->kindFC == 3) p->counter58++;
        break;
    }
    p->state44 = n;
    p->time48 = D_0036BB98.t;
    func_00188DE0(p);
    if (func_001880F0(p)) {
        func_001854C8(D_0036C700, 0x29, p);
        p->Msg(0x18, 0, 0, 0, 0);
        p->V4(0x18, p);
    }
    switch (p->kindFC) {
        case 1: break;
        case 0: case 4: switch (p->state44) {
            case 1: if (p->word60) func_001890B0(p, 4, 0);
            break;
            case 0: case 3: func_00188620(p);
            break;
        }
        break;
        case 3: break;
    }
}
