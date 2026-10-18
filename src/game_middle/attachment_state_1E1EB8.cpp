// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
typedef int Qword __attribute__((mode(TI)));
union Vector {
    Qword q;
    float f[4];
    int i[4];
};
struct Matrix { Vector row[4]; };
struct VirtualEntry { short delta, unused; void *function; };
struct Node {
    Matrix local, world;
    char gap80[0x18];
    short state;
    char gap9A[6];
    Node *parent;
};
struct Owner {
    char prefix[0xC];
    VirtualEntry *methods;
    char gap10[0x18];
    unsigned long flags;
    char gap30[0x18];
    Node *position, *rotation;
};
struct Clip;
struct Event { float time; int kind, tag, unused; };
struct Animation {
    char prefix[0x14];
    Clip *clip;
    int unused18;
    float time;
    char gap20[0x20];
    float rate;
};
struct Root { char prefix[0x50]; Node *node; };
struct Proxy { char prefix[0x1C]; int active; };
struct Goal { char prefix[0xC]; VirtualEntry *methods; };
struct Stretch {
    void *frame;
    Node *first;
    char gap8[0x18];
    Vector position;
    Node *second;
    char gap34[0x6C];
    float tuning;
};
struct Motion;
struct Link {
    char prefix[0x190];
    Owner *owner;
    char gap194[0xC];
    Goal *first;
    int unused1A4;
    Goal *second;
};
struct Actor {
    char prefix[0x50];
    Node *node;
    char gap54[0x14C];
    Vector velocity;
    char gap1B0[0xF8C];
    Animation *animation;
    char gap1140[0x20];
    Proxy *proxy;
    char gap1164[0x3D8];
    Root *root;
    Link *link;
    Motion *m1544, *m1548, *m154C, *m1550;
    int oldPosition, oldRotation;
    char gap155C[0x28];
    int flag;
    int unused1588;
    int state;
    float time;
    char gap1594[0x1A0];
    Node *targetFirst;
    int unused1738;
    Node *targetSecond;
    Motion *m1740, *m1744;
    Stretch *first, *second;
    Motion *m1750, *m1754, *m1758, *m175C;
};
struct Clock { float time, delta; };

extern "C" {
extern Clock D_0036BB98;
extern Matrix D_003174C0;
void func_001309D8(Motion **);
void func_0023EBF8(Owner *, int);
void func_001C7A00(Owner *, Root *, int);
void func_0023FC90(Owner *, int);
Event *func_00136880(Clip *, int);
void func_0028F680(Node *, Node *, Matrix *, Matrix *, float);
Matrix func_001C9708(Actor *, Node *, Matrix *);
void func_001DFAD8(Actor *, Node *, const Matrix *, Qword *, Qword *);
int func_0013B500(Owner *, int);
void func_002558A8(Owner *, Actor *);
void func_001DFEE0(Actor *, Qword, float *, float *, Qword *, Qword *);
Motion *func_00130348(Owner *, Node *, int, float, Qword, Qword);
Qword func_0028E990(Node *, Node *, Qword);
Motion *func_00130078(void *, Node *, int, int, int, Qword);
void func_001E0660(Actor *);
void func_001DE690(Actor *, int);
Motion *func_00130218(Actor *, Node *, int, Stretch *);
Motion *func_001302A0(Actor *, Node *, int, int, void *, Matrix *);
void func_00255908(Owner *);
}

static inline void ClearXYZ(Vector *value)
{
    value->i[0] = value->i[1] = value->i[2] = 0;
}

extern "C" void func_001E1EB8(Actor *actor, int state)
{
    if (actor->state == state)
        return;
    if (actor->state == 1) {
        func_001309D8(&actor->m154C);
        func_001309D8(&actor->m1550);
    }
    actor->state = state;
    actor->time = D_0036BB98.time;
    Owner *owner;
    switch (state) {
    case 0:
        actor->flag = 0;
        break;
    case 1: {
        if (!actor->link)
            goto failed;
        owner = actor->link->owner;
        if ((int)(owner->flags >> 56) & 1)
            goto attach;
        else
            goto failed;
    attach:
        func_0023EBF8(owner, 0);
        actor->oldPosition = owner->position->state;
        actor->oldRotation = owner->rotation->state;
        func_001C7A00(owner, 0, 15);
        func_0023FC90(owner, 1);
        Matrix predicted;
        float duration;
        Event *event = func_00136880(actor->animation->clip, 0x1F5);
        duration = (event->time - actor->animation->time) /
                   actor->animation->rate;
        func_0028F680(actor->root->node, actor->node, &predicted, 0,
                     duration);
        Matrix work = func_001C9708(actor, 0, &predicted);
        predicted = work;
        func_001DFAD8(actor, 0, &predicted, &work.row[0].q, &work.row[1].q);
        if (func_0013B500(owner, 0x3A))
            func_002558A8(owner, actor);
        func_001DFEE0(actor, work.row[1].q, &event->time, &duration,
                     &work.row[2].q, &work.row[3].q);
        actor->m154C = func_00130348(owner, owner->position, 5,
                                    D_0036BB98.time + duration,
                                    work.row[1].q, work.row[3].q);
        VirtualEntry *entry = &owner->methods[40];
        void *receiver = (char *)owner + entry->delta;
        Qword velocity = func_0028E990(owner->position->parent, 0,
                                      work.row[2].q);
        ((void (*)(void *, Qword))entry->function)(receiver, velocity);
        actor->m1550 = func_00130078(owner, owner->rotation, 5, 8, 2,
                                    work.row[0].q);
        break;
    }
    case 2: {
        if (!actor->link)
            goto failed;
        owner = actor->link->owner;
        if ((int)(owner->flags >> 56) & 1)
            goto valid;
    failed:
        func_001E0660(actor);
        actor->link = 0;
        func_001DE690(actor, 0);
        break;
    valid:
        Root *root = actor->root;
        func_001C7A00(owner, root, 15);
        func_0023FC90(owner, 1);
        Vector position, rotation;
        Matrix frame;
        func_001DFAD8(actor, root->node, &D_003174C0,
                     &rotation.q, &position.q);
        actor->m1548 = func_00130078(owner, owner->rotation, 5, 8, 2,
                                    rotation.q);
        actor->m1544 = func_00130078(owner, owner->position, 5, 8, 2,
                                    position.q);
        if (actor->link->first) {
            Goal *goal = actor->link->first;
            Stretch *stretch = actor->first;
            VirtualEntry *entry = &goal->methods[37];
            stretch->frame = ((void *(*)(void *, Matrix *))entry->function)
                ((char *)goal + entry->delta, &frame);
            stretch->position = frame.row[3];
            stretch->tuning = 4.75f;
            actor->m1750 = func_00130218(actor, stretch->first, 5, stretch);
            actor->m1754 = func_00130218(actor, stretch->second, 5, stretch);
            actor->m1740 = func_001302A0(actor, actor->targetFirst, 5, 5,
                                        stretch->frame, &frame);
        }
        if (actor->link->second) {
            Goal *goal = actor->link->second;
            Stretch *stretch = actor->second;
            VirtualEntry *entry = &goal->methods[37];
            stretch->frame = ((void *(*)(void *, Matrix *))entry->function)
                ((char *)goal + entry->delta, &frame);
            stretch->position = frame.row[3];
            stretch->tuning = 1.5f;
            actor->m1758 = func_00130218(actor, stretch->first, 5, stretch);
            actor->m175C = func_00130218(actor, stretch->second, 5, stretch);
            actor->m1744 = func_001302A0(actor, actor->targetSecond, 5, 5,
                                        stretch->frame, &frame);
        }
        if (func_0013B500(owner, 0x3A))
            func_00255908(owner);
        ClearXYZ(&actor->velocity);
        break;
    }
    default:
        break;
    }
    do {
        if (actor->state >= 2)
            break;
        if (actor->state < 0)
            break;
        actor->proxy->active = 1;
        goto end;
    } while (0);
    actor->proxy->active = 0;
end:;
}
