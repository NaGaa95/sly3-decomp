// SLY3_CFLAGS: -Os -G0
// Follower state update: runs the 0..4 state machine until the state settles (0 waits for the owner flag/pending count,
// 1 times out after one second, 2/3 wait for the watched object), then copies each source position to its target.
typedef int qword __attribute__((mode(TI)));
struct VtEntry { short delta; short pad; void *fn; };
struct Link { int w0, w4, w8; struct VtEntry *vt; };
struct Owner { char pad[0x18]; unsigned flags; };
struct Pair { struct Link *source; struct Link *target; int extra; };
struct Follower {
    char prefix[0x134];
    struct Owner *owner;
    char gap138[0x16A4 - 0x138];
    void *watched;
    int state;
    float state_time;
    struct Pair pairs[4];
    int pair_count;
    int count;
    int limit;
    int pending;
    char gap16F0[0x1700 - 0x16F0];
    int cleared;
};
struct Clock { float now, step; };
extern struct Clock D_0036BB98;
void func_001EA4B0(void *self, int state);
int func_001EA940(void *self);
int func_00138AC8(void *object);
void func_001EAB40(void *self);
void func_001EB300(void *self);
void func_001EB340(void *self);
typedef qword *(*GetMatrixFn)(void *);
typedef void (*SetPositionFn)(void *, qword);
void func_001EA750(struct Follower *self)
{
    int state;
    int i;
    do {
        state = self->state;
        switch (state) {
        case 0:
            if (self->pending || (self->owner->flags & 4)) {
                if (self->count >= self->limit)
                    func_001EA4B0(self, 1);
            } else {
                func_001EA4B0(self, func_001EA940(self) ? 2 : -1);
            }
            break;
        case 1:
            if (self->pending == 0 && !(self->owner->flags & 4)) {
                func_001EA4B0(self, func_001EA940(self) ? 2 : -1);
            } else {
                if (D_0036BB98.now - self->state_time > 1.0f)
                    func_001EA4B0(self, 3);
            }
            break;
        case 2:
        case 3:
            if (self->watched == 0 || func_00138AC8(self->watched))
                func_001EA4B0(self, -1);
            break;
        case 4:
            break;
        }
    } while (self->state != state);
    if (self->state < 2) {
        if (self->state >= 0)
            func_001EAB40(self);
        else
            self->cleared = 0;
    } else
        self->cleared = 0;
    for (i = 0; i < self->pair_count; i++) {
        struct Pair *p = &self->pairs[i];
        struct Link *b = p->target;
        struct Link *a = p->source;
        struct VtEntry *e = &b->vt[34];
        ((SetPositionFn)e->fn)((char *)b + e->delta,
                               ((GetMatrixFn)a->vt[36].fn)((char *)a + a->vt[36].delta)[3]);
    }
    func_001EB300(self);
    func_001EB340(self);
}
