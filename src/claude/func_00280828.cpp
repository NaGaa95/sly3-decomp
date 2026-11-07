// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00280828 (agent A60): Sly 3 form of Sly 2 func_00228E50 (SO collider membership + landing impacts), no pins/asm.
// Sly 3: bit 63 of flags 0x120 marks old members, bit 0 of 0x128 new ones; CTX scope; PvAllocSlot; the impact is
// func_00280BF8(p, pos, fall); the stack request pointer is a named local (kept in s5, reused for the signal pair).
typedef int qword __attribute__((mode(TI)));
typedef int S64 __attribute__((mode(DI)));
typedef unsigned int U64 __attribute__((mode(DI)));
union V { qword q; float f[4]; };
struct O;
struct PAIR { O *owner, *object; };
struct VE { short delta, pad; union { qword (*velocity)(void *); int (*test)(void *); void (*signal)(void *, int, PAIR *); } f; };
struct SOURCE { char pad[0x70]; V position; };
struct COLL { SOURCE *source; char pad4[0x14]; S64 flags; char pad20[0x40]; V position; char pad70[0x60]; };
struct PHYS { char pad[0xD4]; float scale; };
struct META { char pad[0x98]; short kind; };
struct LINK { int pad0; LINK *next; int pad8; O *object; };
struct STATE { char pad[0x8]; float minimumZ; char padC[0x58]; LINK *first; };
struct N { O *owner, *object; int pad8; N *next; };
struct O {
    char pad[0xC]; VE *vt; char pad10[0x38]; META *body; char pad4C[0x84]; int count; COLL *colliders; PHYS *physics; STATE *state;
    char padE0[0x40]; S64 flags; S64 flags2; N *first; char pad134[0x1C]; O *recipient; char pad154[0x114]; float height;
};
struct LSG { V first; char pad10[0x50]; };
struct REQ { int size, alignment; };
struct WORLD;
extern WORLD D_00475480;
extern qword D_00317560;
extern "C" {
void func_0023C660(O *);
void func_0013C780(WORLD *);
void func_0013C7D0(WORLD *);
void __3CTX(void *);
void _$_3CTX(void *, int);
int func_00281850(void *, COLL *);
int func_002414D8(O *, int (*)(void *, COLL *), void *, COLL **);
int func_0023FC68(O *);
int func_0028F048(int);
float func_00280EA8(O *, O *, qword *, qword *);
N *func_00281158(WORLD *);
int func_0013B500(O *, int);
int func_00165130(qword, qword, int, COLL **, int, LSG *);
void func_00280BF8(O *, qword, float);
void func_00280740(O *, N **);
}
void *PvAllocSlot(REQ *) __asm__("PvAllocSlot__FP8ALLOCREQ");
union SCRATCH { REQ request; PAIR pair; V velocity; };
struct WORK { char mark[0x10]; SCRATCH scratch; V start, end; LSG intervals[16]; V origin; };
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Min(float a, float b) { return b < a ? b : a; }
static inline int Test(O *o, int slot) { VE *v = o->vt; return v[slot].f.test((char *)o + v[slot].delta); }
static inline qword Velocity(O *o) { VE *v = o->vt; return v[38].f.velocity((char *)o + v[38].delta); }
static inline void Signal(O *o, int event, PAIR *pair) { VE *v = o->vt; v[4].f.signal((char *)o + v[4].delta, event, pair); }
extern "C" void func_00280828(O *p)
{
    WORK work;
    N *n;
    COLL **objects;
    LINK *link;
    int count;
    func_0023C660(p);
    if (!p->count) return;
    for (n = p->first; n; n = n->next) n->object->flags |= (S64)1 << 63;
    func_0013C780(&D_00475480);
    func_0013C7D0(&D_00475480);
    __3CTX(work.mark);
    REQ *request = &work.scratch.request;
    request->size = p->count * 4;
    request->alignment = 16;
    objects = (COLL **)PvAllocSlot(request);
    count = func_002414D8(p, func_00281850, 0, objects);
    for (link = p->state->first; link; link = link->next) {
        O *o = link->object;
        if (!o->physics || o->physics->scale < 1e-4f || func_0023FC68(o) || !func_0028F048(o->body->kind)) continue;
        if (func_00280EA8(p, o, 0, 0) == 0.0f) continue;
        o->flags2 |= 1;
        if (o->flags < 0) continue;
        n = func_00281158(&D_00475480);
        n->owner = p;
        n->object = o;
        n->next = p->first;
        p->first = n;
        if (!p->recipient) continue;
        if (!Test(o, 79)) continue;
        work.scratch.velocity.q = Velocity(o);
        if (work.scratch.velocity.f[2] < -100.0f) {
            int i;
            for (i = 0; i < o->count; i++) {
                COLL *c = &o->colliders[i];
                float dz;
                if (c->flags & 0x90000) continue;
                work.origin.q = D_00317560;
                work.start.q = Sub(c->position.q, work.origin.q);
                work.end.q = Sub(c->source->position.q, work.origin.q);
                if (func_0013B500(o, 0x32)) dz = o->height;
                else dz = o->state->minimumZ - c->source->position.f[2];
                work.start.f[2] += dz;
                work.end.f[2] += dz;
                if (func_00165130(work.start.q, work.end.q, count, objects, 16, work.intervals) > 0) {
                    float fall = Min(-work.scratch.velocity.f[2], 600.0f) * (1.0f / 600.0f);
                    func_00280BF8(p, Add(work.intervals[0].first.q, work.origin.q), fall);
                }
            }
        }
    }
    for (n = p->first; n; n = n->next) {
        O *o = n->object;
        S64 flags = o->flags;
        if (((int)((U64)flags >> 63)) != ((int)o->flags2 & 1)) {
            work.scratch.pair.owner = p;
            work.scratch.pair.object = o;
            Signal(o, o->flags & ((S64)1 << 63) ? 7 : 6, (PAIR *)request);
        }
    }
    func_00280740(p, &p->first);
    _$_3CTX(work.mark, 2);
}
