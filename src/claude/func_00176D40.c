// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00176D40: adapted from Sly 2 func_00199D48 (best supporting contact); the callback now takes a REQ record.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
typedef unsigned long ulong;
typedef union { qword q; float f[4]; int i[4]; } U;
typedef struct CONTACT CONTACT;
typedef struct GROUP { CONTACT *first; struct GROUP *next; } GROUP;
typedef struct { char pad[0x64]; GROUP *groups; char pad68[8]; ulong flags; } EC;
typedef struct { ulong low:48; signed int kind:4; ulong high:12; } FLAG;
typedef struct LO {
    char pad[0x10]; struct LO *parent;
    char pad14[0xDC - 0x14]; EC *ec;
    char padE0[0x120 - 0xE0];
    FLAG flags;
} LO;
typedef struct SX { char pad[0xA4]; int xA4; } SX;
typedef struct { SX *psx; LO *owner; char pad8[0x84 - 8]; void *bsp; char pad88[0xC0 - 0x88]; int xC0; } SHAPE;
typedef struct { SHAPE *shape; void *spool; LO *object; LO *lo; U position, local, world; } ENDPOINT;
struct CONTACT { ENDPOINT endpoints[2]; U normal; float distance, friction, response; int kind; void *info[2]; int tag; CONTACT *next; U difference; };
typedef struct { SHAPE *shape; int kind; void *info; int pad; qword pos; qword dir; } REQ;
extern qword D_00317550;
extern float D_00349880[];
extern char D_00475480[];
qword func_0028E910(int n, SX *psx, qword pos);
int func_00176960(LO *p, REQ *preq);
void func_001CBC30(void *p, int n, CONTACT **ppc);
void func_0018B1E0(SHAPE *p);
int func_00119C90(void *bsp, void *pv, qword pos);
static __inline__ qword Scalar(float f)
{
    qword q;
    __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f));
    return q;
}
static __inline__ qword Project(qword position, qword normal, qword back, qword axis, qword lift)
{
    __asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddax.xyzw $ACC,%4,%3x\n\tvmaddx.xyzw %0,%2,%1x" : "+j"(position) : "j"(lift), "j"(axis), "j"(back), "j"(normal));
    return position;
}
static __inline__ int Kind(LO *lo) { return lo->flags.kind; }
static __inline__ int Side(LO *owner, CONTACT *contact)
{
    uint different = (uint)owner ^ (uint)contact->endpoints[0].object;
    return different != 0;
}
static __inline__ ENDPOINT *Opposite(CONTACT *contact, int side)
{
    int one = 1;
    return (ENDPOINT *)((char *)contact + ((one - side) << 6));
}
static __inline__ ENDPOINT *Opposite2(CONTACT *contact, int side)
{
    int one = 1;
    return (ENDPOINT *)(((one - side) << 6) + (uint)contact);
}
int func_00176D40(LO *p, REQ *preq)
{
    REQ req;
    U point, scalar;
    CONTACT *contact;
    GROUP *group;
    CONTACT *best = 0;
    int bestSide;
    qword bestDir;
    float bestHeight = -3.40282347e+38f;
    for (group = p->ec->groups; group; group = group->next) {
        for (contact = group->first; contact; contact = contact->next) {
            int side = Side(p, contact);
            SHAPE *shape = Opposite(contact, side)->shape;
            LO *lo;
            void *info;
            for (lo = shape->owner; lo; lo = lo->parent)
                if (Kind(lo) == 2) break;
            if (lo) continue;
            switch (contact->kind) {
            case 1: if (side == 0) continue; info = contact->info[0]; break;
            case 3: if (side == 0) info = contact->info[1]; else info = contact->info[0]; break;
            case 2: if (side == 1) continue; info = contact->info[1]; break;
            default: continue;
            }
            req.shape = shape;
            req.pos = func_0028E910(0, shape->psx, Opposite2(contact, side)->position.q);
            req.kind = contact->kind;
            req.info = info;
            req.dir = D_00317550;
            if (!func_00176960(p, &req)) continue;
            if ((p->ec->flags & 2) || (shape->owner->ec->flags & 2))
                func_001CBC30(D_00475480, 1, &contact);
            if (0.0f < D_00349880[side] * contact->difference.f[2]) continue;
            {
                qword back, lift, value;
                back = Scalar(-60.0f);
                lift = Scalar(70.0f);
                value = Project(Opposite2(contact, side)->position.q, req.dir, back, D_00317550, lift);
                scalar = (U){back};
                point.q = value;
                scalar = (U){lift};
                if (shape->xC0 != shape->psx->xA4)
                    func_0018B1E0(shape);
                if (func_00119C90(shape->bsp, (void *)0x7FFFFFFF, point.q)) continue;
                if (Opposite(contact, side)->position.f[2] < bestHeight) continue;
                bestDir = req.dir;
                best = contact;
                bestSide = side;
                bestHeight = Opposite(best, side)->position.f[2];
            }
        }
    }
    if (best) {
        ENDPOINT *pe = Opposite(best, bestSide);
        SHAPE *shape = pe->shape;
        preq->shape = shape;
        preq->pos = func_0028E910(0, shape->psx, pe->position.q);
        preq->kind = best->kind;
        preq->info = !bestSide ? best->info[1] : best->info[0];
        preq->dir = bestDir;
        return 1;
    }
    return 0;
}
