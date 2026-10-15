// SLY3_CFLAGS: -Os -G0
typedef struct ACTOR_VIEW ACTOR_VIEW;
typedef struct ACTOR_METHOD {
    short adjustment;
    short padding;
    int (*invoke)(ACTOR_VIEW *receiver, int mask);
} ACTOR_METHOD;
struct ACTOR_VIEW {
    char opaque[0xC];
    ACTOR_METHOD *methods;
};
typedef struct ACTOR_STATE_VIEW {
    ACTOR_VIEW *owner;
    int state;
    float enteredAt;
    int suppressionCount;
} ACTOR_STATE_VIEW;
typedef char ActorMethodRecordIsEightBytes[(sizeof(ACTOR_METHOD) == 8) ? 1 : -1];
typedef char ActorStateConsumedPrefixIsSixteenBytes[(sizeof(ACTOR_STATE_VIEW) == 16) ? 1 : -1];
extern struct { float current; float delta; } D_0036BB98;
int func_00259BD8(ACTOR_STATE_VIEW *state);
void func_00259CA8(ACTOR_STATE_VIEW *state, int nextState);

void func_00259A40(ACTOR_STATE_VIEW *p)
{
    int allowed, previous;
    if (p->suppressionCount > 0)
        return;
    allowed = func_00259BD8(p);
    do {
        previous = p->state;
        switch (previous) {
        case 0:
            if (allowed)
                func_00259CA8(p, 1);
            break;
        case 1:
            if (!allowed)
                func_00259CA8(p, 0);
            else if (D_0036BB98.current - p->enteredAt > 0.1f &&
                     !p->owner->methods[80].invoke(
                         (ACTOR_VIEW *)((char *)p->owner + p->owner->methods[80].adjustment), 0x4000))
                func_00259CA8(p, 2);
            break;
        case 2:
            if (!allowed)
                func_00259CA8(p, 0);
            break;
        }
    } while (p->state != previous);
}
