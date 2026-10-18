struct MessageObject {
    char pad[0x164];
    int active;
    int pending;
};

struct MessageLink {
    char pad[0xC];
    struct MessageObject *target;
};

struct Owner {
    char pad[0x29C];
    char component[0x4C4 - 0x29C];
    struct MessageLink *link;
};

struct Message {
    struct MessageObject *target;
    struct Owner *source;
};

void func_001F4278(struct Owner *, int, struct Message *);
void func_0025A030(struct MessageLink *, struct MessageObject *);
void func_00238610(void *, int, struct Message *);

void func_00252440(struct Owner *owner, int kind, struct Message *message)
{
    func_001F4278(owner, kind, message);
    switch (kind) {
    case 6:
        if (message->source == owner &&
            (message->target->active || message->target->pending))
            func_0025A030(owner->link, message->target);
        break;
    case 7:
        if (message->source == owner && message->target == owner->link->target)
            func_0025A030(owner->link, 0);
        break;
    }
    func_00238610(owner->component, kind, message);
}
