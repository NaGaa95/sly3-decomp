// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001EAB40: tracker refresh: drop stale entries, then scan the global node list for new visible targets.
// The list address is taken before the func_00153290 call (its high part is computed ahead of the call).
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct M4 { qword r[4]; };
struct Object { unsigned char prefix[0xC]; Method *methods; };
struct Link { Object *first; };
struct Node {
    unsigned char prefix0[0xC];
    Method *methods;
    unsigned char gap10[4];
    Link *link;
    unsigned char gap18[0xD0 - 0x18];
    Node *next;
    unsigned char gapD4[4];
    unsigned flags;
    float radius;
};
struct Entry { Node *owner; Object *object; float time; };
struct Tracker {
    unsigned char prefix0[0x16B0];
    Entry entries[4];
    int count;
    unsigned char gap16E4[0x16F0 - 0x16E4];
    float age;
    unsigned char gap16F4[0x1700 - 0x16F4];
    int cleared;
};
struct Scope { unsigned char storage[1]; ~Scope() {} };
struct Ctx { unsigned char storage[1]; ~Ctx() {} };
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=r"(q) : "f"(f)); }
    VU_FLOAT(const float *pf) { __asm__("lw %0, %1" : "=r"(q) : "m"(*pf)); }
};
struct VU_FLOATC {
    qword q;
    VU_FLOATC(const VU_FLOAT &o) { q = o.q; }
    VU_FLOATC(const VU_FLOATC &o) { q = o.q; }
};
struct NodeList { Node *first; };
extern NodeList D_00479AD8;
extern struct { float time; } D_0036BB98;
extern char D_00475480[];
extern "C" {
void func_001D2770(Ctx *ctx);
void func_001D2798(Ctx *ctx, int n);
void func_002BC490(void *p, int n);
void *func_001F4A80(Tracker *self);
void *func_00153290(Tracker *self, int mode);
int func_001EAF80(Tracker *self, void *owner);
int func_00167F60(void *hero, qword pos, VU_FLOAT range);
void func_001EAA00(Tracker *self, qword pos, float *out);
void *func_00291F38(void *destination, const void *source, unsigned int bytes);
int func_0013B500(void *object, int kind);
void func_0025CF18(void *pg, qword a, qword b, int (*pfn)(), int c, int *pn0, int *pn1);
int func_0025CEC8();
int func_00165000(int n, qword a, qword b, int n0, int n1, void *phit);
void func_001EB118(Tracker *self, void *owner);
}
static inline M4 *Matrix(void *object)
{
    Method *method = &((Object *)object)->methods[36];
    return ((M4 *(*)(void *))method->function)((char *)object + method->adjustment);
}
static inline qword Position(void *object) { return Matrix(object)->r[3]; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Cross(qword a, qword b) { qword r; __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(a), "j"(b), "j"(a), "j"(a)); return r; }
static inline qword Normalize(qword v)
{
    qword m, one, l, r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(m), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(m));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static inline qword ScaleX(qword v, VU_FLOATC s)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s.q));
    return r;
}
extern "C" void func_001EAB40(Tracker *self)
{
    int i = 0;
    Object *hero = (Object *)func_001F4A80(self);
    qword heroPos = Position(hero);
    self->cleared = 0;
    while (i < self->count) {
        Entry *e = &self->entries[i];
        int stale = 0;
        if (!func_001EAF80(self, e->owner))
            stale = 1;
        else if (D_0036BB98.time - e->time < self->age)
            stale = func_00167F60(hero, Position(e->owner), VU_FLOAT(50.0f)) == 0;
        if (stale) {
            Object *object = e->object;
            Method *method = &object->methods[9];
            ((void (*)(void *))method->function)((char *)object + method->adjustment);
            func_00291F38(e, e + 1, (self->count - i) * sizeof(Entry) - sizeof(Entry));
            self->count--;
        } else {
            i++;
            func_001EAA00(self, Position(e->owner), 0);
        }
    }
    NodeList *list = &D_00479AD8;
    void *gate = func_00153290(self, 0);
    Scope scope;
    for (Node *node = list->first; node; node = node->next) {
        Ctx ctx;
        if (!(node->flags & 0x200017E))
            continue;
        if (!func_001EAF80(self, node))
            continue;
        Object *first = node->link->first;
        if (gate && func_0013B500(first, 0x6F))
            continue;
        int found = 0;
        for (int j = 0; j < self->count; j++) {
            if (self->entries[j].owner == node) {
                found = 1;
                break;
            }
        }
        if (found)
            continue;
        qword nodePos = Position(node);
        VU_FLOAT range(&node->radius);
        if (!func_00167F60(hero, nodePos, range))
            continue;
        float out;
        func_001EAA00(self, nodePos, &out);
        if (0.0f < out)
            continue;
        qword probe[4];
        int n0, n1;
        unsigned k;
        int hits = 0;
        func_001D2770(&ctx);
        func_0025CF18(D_00475480, nodePos, heroPos, func_0025CEC8, 0, &n0, &n1);
        {
            qword up = Matrix(hero)->r[1];
            qword dn = Normalize(Sub(heroPos, nodePos));
            qword side = Normalize(Cross(up, dn));
            qword center = Add(nodePos, ScaleX(dn, range));
            probe[1] = Add(center, ScaleX(up, range));
            probe[2] = Sub(center, ScaleX(up, range));
            probe[3] = Add(center, ScaleX(side, range));
            probe[0] = center;
        }
        qword *pq = probe;
        for (k = 0; k < 4; k++, pq++) {
            if (func_00165000(0, heroPos, *pq, n0, n1, 0))
                hits++;
        }
        if (hits == 4) {
            func_001D2798(&ctx, 2);
            continue;
        }
        func_001EB118(self, node);
        func_001D2798(&ctx, 2);
    }
    func_002BC490(&scope, 2);
}
