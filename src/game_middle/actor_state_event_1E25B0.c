// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct Actor {
    char prefix[0x9FC];
    int request;
    char gapA00[0x11B4 - 0xA00];
    void *payload;
    char gap11B8[0x13F4 - 0x11B8];
    int saved;
    char gap13F8[0x1520 - 0x13F8];
    int state;
    char gap1524[0x1538 - 0x1524];
    int flag1538;
    char gap153C[0x1578 - 0x153C];
    int flag1578;
    char gap157C[0x1AAC - 0x157C];
    int current;
};

void func_001E2778(struct Actor *, int);
void func_00154460(struct Actor *, int);
void func_001545A8(struct Actor *, int);
void func_001DE690(struct Actor *, int);
void func_001E16E8(struct Actor *, int);
void func_001E2E88(struct Actor *, int);
void func_001B40F0(void *, int, void *, void *);

void func_001E25B0(struct Actor *actor, int request)
{
    func_001E2778(actor, request);
    switch (request) {
    case 18:
        func_00154460(actor, request);
        func_001DE690(actor, 13);
        func_001E16E8(actor, 0);
        func_001E16E8(actor, 1);
        break;
    case 21:
        actor->request = request;
        actor->saved = actor->current;
        func_001B40F0((char *)actor + 0x500, 11, 0, 0);
        break;
    case 24:
        func_00154460(actor, request);
        actor->flag1578 = 1;
        func_001DE690(actor, 8);
        break;
    case 23:
        func_00154460(actor, request);
        actor->flag1538 = 1;
        func_001DE690(actor, 3);
        break;
    case 20:
        actor->request = 20;
        func_001B40F0((char *)actor + 0x500, 11, actor->payload, 0);
        break;
    case 17:
        if (actor->state == 22)
            func_001E2E88(actor, 2);
        else
            func_001DE690(actor, 22);
        break;
    default:
        func_001545A8(actor, request);
        break;
    }
}
