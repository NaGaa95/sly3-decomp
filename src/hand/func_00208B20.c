// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct ACTOR_VIEW;
struct STATE_VIEW;
/* Field names describe a consumed view, not an asserted complete class. */
/* The original GCC PMF is eight bytes, passed as one 64-bit GP value. */
struct PMF8 {
    short delta, index;
    union {
        void (*direct)(struct ACTOR_VIEW *, struct STATE_VIEW *);
        short vtableOffset;
    } target;
};
union FLOAT_WORD {
    unsigned int bits;
    float scalar;
};
struct MATRIX4 {
    qword row[4];
};
struct VE {
    short delta, padding;
    const struct MATRIX4 *(*matrix)(void *);
};
struct ACTOR_VIEW {
    char opaque0[0xC];
    struct VE *table;
    char opaque10[0x164-0x10];
    int flags164;
};
/* Actual slot 36 returns a MATRIX4 pointer; row 3 is a full 128-bit value. */
static __inline__ qword Position(struct ACTOR_VIEW *p) {
    struct VE *entry = &p->table[36];
    return entry->matrix((char *)p + entry->delta)->row[3];
}
struct SOURCE_SLOT {
    void *instance;
};
struct EFFECT {
    char opaque0[0x64];
    float gain64;
};
struct TARGET_VIEW {
    char pad[0xD0];
    int flagsD0;
};
struct STATE_VIEW {
    struct ACTOR_VIEW *actor;
    struct SOURCE_SLOT *source;
    float weight8;
    char p0[0x1C - 0xC];
    float weight1C;
    char p1[0x30 - 0x20];
    struct EFFECT *effect;
    void *parameter34;
    void *channel;
    char p2[0x80 - 0x3C];
    void *task80;
    struct TARGET_VIEW *baselineTarget;
    union FLOAT_WORD targetParameter;
    struct TARGET_VIEW *selectedTarget;
    int mode;
    void *task94;
    void *task98;
    void *task9C;
    struct TARGET_VIEW *objectA0;
    int state;
    float stateStartTime;
    struct SOURCE_SLOT localSource;
};
struct CLOCK {
    float t;
    float dt;
};
typedef char CheckPmf8[(sizeof(struct PMF8) == 8) ? 1 : -1];
typedef char CheckFloatWord4[(sizeof(union FLOAT_WORD) == 4) ? 1 : -1];
typedef char CheckMatrix64[(sizeof(struct MATRIX4) == 64) ? 1 : -1];
typedef char CheckStatePrefixB0[(sizeof(struct STATE_VIEW) == 0xB0) ? 1 : -1];

extern struct CLOCK D_0036BB98;
extern const struct PMF8 D_00325890;
extern char D_00475480[];
void func_001309D8(void **p);
int func_0013B500(struct TARGET_VIEW *p, int n);
void func_0022EA88(struct TARGET_VIEW *p, qword q, const void *metric, qword *point, qword *direction, float *parameter, float *finalParameter);
struct TARGET_VIEW *func_00208AA0(struct ACTOR_VIEW *pw, struct TARGET_VIEW *po);
qword func_0028B388(void *a, void *b);
void *func_00130078(struct ACTOR_VIEW *p, void *q, int a, int b, int c, qword d);
void func_00148938(void *p);
void func_0015DCD0(void *pg, struct ACTOR_VIEW *pw, struct PMF8 p8, struct STATE_VIEW *p);
void func_00137628(struct SOURCE_SLOT *source);
void func_00137588(struct EFFECT *effect, struct ACTOR_VIEW *actor, int flags,
                   struct SOURCE_SLOT *source, float gain, float start);
void func_00208B20(struct STATE_VIEW *p, int n) {
    if (n == p->state) return;
    if (p->state == 1) {
        func_001309D8(&p->task94);
        func_001309D8(&p->task9C);
    }
    p->state = n;
    p->stateStartTime = D_0036BB98.t;
    switch (n) {
    case 0:
    case 1:
        p->selectedTarget = p->baselineTarget;
        p->mode = 1;
        if (func_0013B500(p->baselineTarget, 9)) {
            struct TARGET_VIEW *po = p->baselineTarget;
            func_0022EA88(po, Position(p->actor), 0, 0, 0, 0, &p->targetParameter.scalar);
            p->mode = 0;
        }
        else if (func_0013B500(p->baselineTarget, 0x12) && (p->baselineTarget->flagsD0 & p->actor->flags164)) {
            p->mode = 2;
        }
        else if (func_0013B500(p->baselineTarget, 0x2F)) {
            struct TARGET_VIEW *po = func_00208AA0(p->actor, p->baselineTarget);
            if (po) {
                p->selectedTarget = po;
                p->mode = 2;
            }
        }
        if (p->mode == 2)
            p->task80 = func_00130078(p->actor, p->channel, 5, 8, 3,
                                     func_0028B388(p->channel, p->channel));
        p->weight1C = p->weight8 = 0.5f;
        func_00148938(p->effect);
        func_0015DCD0(D_00475480, p->actor, D_00325890, p);
        break;
    case -1:
        func_001309D8(&p->task80);
        p->mode = n;
        p->selectedTarget = 0;
        p->baselineTarget = 0;
        /* The original clears the float storage with a word store. */
        p->targetParameter.bits = 0;
        break;
    }
    if (p->source == &p->localSource) {
        if (p->state == -1)
            func_00137628(p->source);
        else
            func_00137588(p->effect, p->actor, 1, p->source,
                           p->effect->gain64 * 0.5f, 0.0f);
    }
}
