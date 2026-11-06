// Apply a hit to the two health counters: accept the hit in modes 2/4/5 (flag 2, accepted by the object, attacker derived from the actor classes), scale the damage, pick the side that was hit (A, B or both by the impact angle) and subtract from the current and saved counters; then notify or switch to the dead state (mode 4 with the owner in phase 2 can revive with 1 point).
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
enum Side { SIDE_NONE = -1, SIDE_A, SIDE_B, SIDE_BOTH };
struct Link { struct Owner *owner; };
struct Owner { char pad0[0xC]; struct VTE *pvt; char pad10[0x1B8 - 0x10]; int n1B8; };
struct Core { char pad0[0x14]; struct Link *link; };
struct Obj { char pad0[0xC]; struct VTE *pvt; char pad10[4]; struct Link *link; char pad18[0x1E8 - 0x18]; struct Core *core; };
struct Hit { char pad0[0x14]; struct Obj *obj; char pad18[8]; int arg20; int damage; int kill; char pad2C[0x50 - 0x2C]; unsigned int flags; };
struct Range { float lo, hi; };
struct Self {
    char pad0[0xC]; struct VTE *pvt;
    char pad10[0x190 - 0x10];
    int cur[2];
    char pad198[0x1A0 - 0x198];
    int save[2];
    char pad1A8[4];
    enum Side side;
    int mode;
    char pad1B4[4];
    int n1B8;
    char pad1BC[0x3F8 - 0x1BC];
    struct Range tilt;
    char pad400[0x4F4 - 0x400];
    int n4F4;
};
extern float D_00325BB4;
extern qword D_00317530;
extern char D_0036C700[];
extern void *D_00468D24;
int func_0013B500(void *, int);
int func_001C8F20(void *, void *);
void func_001F4DD8(struct Self *, struct Obj *, float, int);
qword func_001C94E8(struct Obj *, struct Self *, qword);
qword func_001C9428(int, struct Self *, qword);
float func_002A3EE8(float, float);
float func_0011E3B8(float);
int func_0011EE30(struct Range *, float);
void func_00217F68(struct Self *, int);
int func_0021A4E8(void *, struct Self *);
void func_002159D8(struct Self *, int);
void func_00215FD0(struct Self *, int);
void func_001854C8(void *, int, struct Self *);
static __inline__ float GetX(qword v) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(v)); return f; }
static __inline__ float GetY(qword v) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(v)); return f; }
static __inline__ int Max0(int v) { return v < 0 ? 0 : v; }
int func_00214370(struct Self *self, struct Hit *hit)
{
    int isActor;
    struct Owner *owner;
    switch (self->mode) {
    case 2:
    case 4:
    case 5:
        break;
    default:
        return 0;
    }
    if (!(hit->flags & 2))
        return 0;
    {
        struct VTE *e = &self->pvt[80];
        if (((int (*)(void *, int))e->pfn)((char *)self + e->d, hit->arg20))
            return 0;
    }
    isActor = func_0013B500(hit->obj, 0x59);
    if (isActor) {
        owner = hit->obj->core->link->owner;
        if (func_001C8F20(owner, self))
            return 0;
    } else {
        owner = hit->obj->link->owner;
    }
    if (!func_0013B500(owner, 0x58))
        return 0;
    func_001F4DD8(self, hit->obj, D_00325BB4, hit->arg20);
    if (self->n4F4 == 0x3F)
        hit->damage = hit->damage / 2;
    if (self->n1B8 == 2 && owner->n1B8 == self->n1B8)
        hit->damage = hit->damage / 4;
    if (hit->kill) {
        self->cur[0] = 0;
        self->cur[1] = 0;
    } else {
        self->side = SIDE_NONE;
        if (isActor) {
            qword r = func_001C94E8(hit->obj, self, D_00317530);
            float y = GetY(r);
            float angle = func_0011E3B8(func_002A3EE8(y, __builtin_fabsf(GetX(r))));
            if (func_0011EE30(&self->tilt, angle))
                self->side = SIDE_BOTH;
            else if (y < 0.0f)
                self->side = SIDE_A;
            else
                self->side = SIDE_B;
        } else {
            struct VTE *e = &hit->obj->pvt[36];
            struct M4 *m = ((struct M4 *(*)(void *))e->pfn)((char *)hit->obj + e->d);
            qword r = func_001C9428(0, self, m->r[3]);
            if (0.0f < GetY(r))
                self->side = SIDE_A;
            else
                self->side = SIDE_B;
        }
        switch (self->side) {
        case SIDE_A:
        case SIDE_B:
            self->cur[self->side] = Max0(self->cur[self->side] - hit->damage);
            if (isActor) {
                self->save[self->side] = Max0(self->save[self->side] - hit->damage);
                func_00217F68(self, self->side);
            }
            break;
        case SIDE_BOTH: {
            float scale = self->n1B8 == 2 ? 3.0f : 2.0f;
            int d = (int)((float)hit->damage * scale);
            self->cur[0] = Max0(self->cur[0] - d);
            self->cur[1] = Max0(self->cur[1] - d);
            if (isActor) {
                self->save[0] = Max0(self->save[0] - d);
                self->save[1] = Max0(self->save[1] - d);
                func_00217F68(self, 0);
                func_00217F68(self, 1);
            }
            break;
        }
        default:
            break;
        }
    }
    if (self->cur[0] <= 0 || self->cur[1] <= 0) {
        if (self->n1B8 == 2 && self->mode == 4 && func_0021A4E8(D_00468D24, self)) {
            func_002159D8(self, 5);
            self->cur[0] = 1;
            self->cur[1] = 1;
            func_001854C8(D_0036C700, 0xF, self);
        } else {
            func_00215FD0(self, 2);
            func_002159D8(self, 7);
        }
    } else {
        if (self->n1B8 == 2)
            func_001854C8(D_0036C700, 0xF, self);
        else
            func_001854C8(D_0036C700, 0xA, self);
    }
    return 1;
}
