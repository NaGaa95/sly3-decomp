// SLY3_CFLAGS: -Os -G0
typedef int AlternatePosition __attribute__((mode(TI)));
struct AlternateSelectActor;

struct AlternateActorLink {
    int word0;
    struct AlternateSelectActor *actor;
};

struct AlternateEndpoint {
    struct AlternateActorLink *link;
    int word4;
    void *key;
    void *owner;
    AlternatePosition origin;
    AlternatePosition position;
    AlternatePosition word30;
};

struct AlternateCandidate {
    struct AlternateEndpoint endpoints[2];
    char gap80[8];
    float strength;
    int word8C;
    float distance;
    char gap94[0x18];
    struct AlternateCandidate *next;
};

struct AlternateGroup {
    struct AlternateCandidate *first;
    struct AlternateGroup *next;
};

struct AlternateWorld {
    char prefix[0x60];
    void *key;
    struct AlternateGroup *groups;
};

struct AlternateSelectActor {
    char prefix[0xDC];
    struct AlternateWorld *world;
    char gapE0[0x240 - 0xE0];
    AlternatePosition origin;
    char gap250[0x1520 - 0x250];
    int state;
    char gap1524[0x1B00 - 0x1524];
    struct AlternateCandidate *alternate;
    int selected;
    float selected_time;
    void *alternate_owner;
};

struct AlternateClock { float now, step; };
extern struct AlternateClock D_0036BB98;
void func_0024E9E0(void *receiver);

void func_001E1C68(struct AlternateSelectActor *p)
{
    func_0024E9E0(p);
    if (p->state == 22) {
        struct AlternateCandidate *best = 0;
        struct AlternateGroup *group;
        float minimum = 3.402823466e+38f;
        void *key = p->world->key;
        for (group = p->world->groups; group; group = group->next) {
            struct AlternateCandidate *candidate;
            for (candidate = group->first; candidate; candidate = candidate->next) {
                int selected = candidate->endpoints[0].key != key;
                if (candidate->endpoints[selected].link->actor == p &&
                    !(candidate->strength < 0.7f)) {
                    float distance = candidate->distance;
                    if (distance < minimum) {
                        p->selected = selected;
                        minimum = distance;
                        best = candidate;
                    }
                }
            }
        }
        p->alternate = best;
        if (best) {
            unsigned int offset = (1U - (unsigned int)p->selected) * sizeof(struct AlternateEndpoint);
            struct AlternateEndpoint *other = (struct AlternateEndpoint *)(offset + (unsigned int)best);
            p->selected_time = D_0036BB98.now;
            p->origin = other->origin;
            p->alternate_owner = other->owner;
        }
    } else {
        p->alternate = 0;
    }
}
