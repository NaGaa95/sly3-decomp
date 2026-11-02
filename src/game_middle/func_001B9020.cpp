// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001B9020: per-frame update of the hero's airborne state machine (Sly 2 func_00197500 relative): button handling
// (double jump, grab, gadget), then one handler per air state (jump table of 23 states). The loop repeats while a handler
// changes the state. Virtual calls are written as vtable-entry helpers (delta + function pointer).
typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
union U { qword q; float f[4]; int i[4]; };
struct M4 { U r[4]; };
struct VTE { short delta, pad; void *fn; };
struct VU_FLOAT { qword q; };

static inline VU_FLOAT VuFloat(float g) { VU_FLOAT v; __asm__("qmtc2.ni %1,%0" : "=j"(v.q) : "r"(g)); return v; }
static inline VU_FLOAT VuFloatBits(int bits) { VU_FLOAT v; __asm__("qmtc2.ni %1,%0" : "=j"(v.q) : "r"(bits)); return v; }
static inline qword QwSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwScale(qword a, VU_FLOAT g) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(g.q)); return r; }
static inline qword QwDivQ(qword v, qword l) { qword r; __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "j"(l)); return r; }
static inline float GFromQw(qword q) { float g; __asm__("mtc1 %1,%0" : "=f"(g) : "r"(q)); return g; }
static inline float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static inline float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static inline qword QwFromXYZ(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
static inline float GMinOf(float a, float b) { return (a < b) ? a : b; }

struct XF { char pad0[0xA0]; void *parent; char padA4[4]; float ref; char padAC[4]; U v; };
struct PCTL { char pad0[8]; float sLeft; char padC[0x18 - 0xC]; unsigned grfbtn; char pad1C[0x2C - 0x1C]; VTE *vt; };
struct ACTOR {
    char pad0[0xC]; VTE *vt; char pad10[0x48 - 0x10]; XF *xf; char pad4C[0xD8 - 0x4C]; char *physics;
    char pad_DC[0x134 - 0xDC]; PCTL *pctl; char pad138[0x260 - 0x138]; U offset;
    char pad270[0x500 - 0x270]; char jtgrab[0x10]; char pad510[0xF60 - 0x510]; char jtmode[0x10];
    char padF70[0x1108 - 0xF70]; void *x1108; char pad110C[0x113C - 0x110C]; void *x113C;
    char pad1140[0x1408 - 0x1140]; float x1408; char pad140C[0x19F0 - 0x140C]; int x19F0;
};
struct LO { char pad0[0x28]; ulong flags; char pad30[0x178 - 0x30]; int x178; };
struct TREEOBJ { char pad0[0xDC]; void *ptree; };
struct EDGE { char pad0[4]; TREEOBJ *plo; char pad8[0x18 - 8]; ulong flags; };
struct ACT { char pad0[4]; int x4; int x8; char padC[0x1C - 0xC]; float tEnd; char pad20[0x30 - 0x20]; U goalVel; };
struct CONTEXT {   // the air-state context (same object as func_001B7268's CONTEXT)
    ACTOR *actor; int kind; int n2; LO *plo; char pad10[0x1C - 0x10]; int state; float tState; int x24; int count; int x2C;
    char pad30[0x3C - 0x30]; int x3C; char pad40[0x80 - 0x40]; EDGE *edge; char pad84[0xA0 - 0x84]; U normalEdge;
    char padB0[0xC0 - 0xB0]; void *asegC0; char padC4[0xD4 - 0xC4]; void *asegD4; char padD8[0xE8 - 0xD8]; void *asegs[5];
    char padFC[0x190 - 0xFC]; int limit; char pad194[0x1B0 - 0x194]; void *placeObject; void *placeSpot; void *placePart;
    char pad1BC[0x1C0 - 0x1BC]; U placePos; ACT *act; char pad1D4[0x200 - 0x1D4];
};
struct CLOCK { float t, dt; };
struct SHEET { char pad0[0x18E0]; char moverec[4]; int moveState; char pad18E8[0x1944 - 0x18E8]; void *aseg; };

extern "C" {
extern CLOCK g_clock;
extern ACTOR *D_0036B250;
extern ACTOR *D_00370AC0;
extern SHEET *D_0038AE90;
int func_001BADC0(ACTOR *);
void func_001BD6C8(CONTEXT *);
int func_002502F0(float, ACTOR *);
int func_00173428(void *);
void func_001B7268(CONTEXT *, int, int, int, float);
void func_001BBCA8(CONTEXT *, void *);
void func_001B77F8(CONTEXT *, int, void *);
void func_001B8EB0(CONTEXT *);
float func_001368E0(void *, int);
void func_002734E8(void *, int);
int func_001BADF8(float, ACTOR *, float *);
void func_001C0538(ACTOR *, void *);
void func_001B40F0(void *, int, int, int);
int func_001BAD30(CONTEXT *, EDGE **);
int func_00156998(ACTOR *);
int func_001A7A80(PCTL *, int, float);
int func_00176960(ACTOR *, EDGE **);
void func_0024E8E8(ACTOR *, qword);
void func_001BDA88(void *, int, int);
int func_00138AC8(void *);
int func_0023E130(ACTOR *);
unsigned func_00154798(ACTOR *, int);
int func_0013B500(void *, int);
qword func_001BB4E8(CONTEXT *, int);
qword func_001C9428(void *, int, qword);
int func_0011EA28(float *, float, float, float);
void func_00137588(void *, ACTOR *, int, void **, float, float);
void func_0028B1B0(int, int);
qword func_001C03A0(float, ACTOR *, void *);
qword func_0028E910(int, void *, qword);
void func_001305C8(ACT *, qword, qword);
void func_001BD520(CONTEXT *);
int func_002496C8(LO *);
int func_001A29B0(LO *);
}

static inline M4 *MatrixOf(ACTOR *p) { VTE &v = p->vt[36]; return ((M4 *(*)(void *))v.fn)((char *)p + v.delta); }
static inline qword GetVelocity(ACTOR *p) { VTE &v = p->vt[38]; return ((qword (*)(void *))v.fn)((char *)p + v.delta); }
static inline void SetVelocity(ACTOR *p, const qword &q) { VTE &v = p->vt[40]; ((void (*)(void *, qword))v.fn)((char *)p + v.delta, q); }
static inline void Leave(ACTOR *p, int n) { VTE &v = p->vt[99]; ((void (*)(void *, int))v.fn)((char *)p + v.delta, n); }
static inline int HasGadget(ACTOR *p, int n) { VTE &v = p->vt[113]; return ((int (*)(void *, int))v.fn)((char *)p + v.delta, n); }
static inline void StartGadget(ACTOR *p, int n) { VTE &v = p->vt[114]; ((void (*)(void *, int))v.fn)((char *)p + v.delta, n); }
static inline unsigned Pressed(PCTL *c, unsigned grf, const float &dt)
{
    VTE &v = c->vt[1];
    return ((unsigned (*)(void *, unsigned, float))v.fn)((char *)c + v.delta, grf, dt);
}
static inline void Clear(PCTL *c, unsigned grf) { VTE &v = c->vt[2]; ((void (*)(void *, unsigned))v.fn)((char *)c + v.delta, grf); }

extern "C" void func_001B9020(CONTEXT *self)
{
    U posHero;
    U vel;
    int prev;
    int floor;
    PCTL *pctl;
    posHero.q = MatrixOf(self->actor)->r[3].q;
    vel.q = GetVelocity(self->actor);
    pctl = self->actor->pctl;
    floor = func_001BADC0(self->actor);
    do {
        prev = self->state;
        if (self->plo != 0) {
            if (((int)(self->plo->flags >> 56) & 1) == 0)
                func_001BD6C8(self);
        }
        switch (self->state) {
        case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22:
            break;
        default:
            if (self->count < self->limit && self->state != 2) {
                if (Pressed(pctl, 0x40, 0.1f)) {
                    if (!func_002502F0(0.075f, self->actor)) {
                        void *x = self->actor->x1108;
                        int busy = 0;
                        if (x) busy = func_00173428(x) != 0;
                        if (!busy) {
                            Clear(pctl, 0x40);
                            func_001B7268(self, 6, self->n2, 0, 1.0f);
                            goto next;
                        }
                    }
                }
            }
            if (Pressed(pctl, 0x20, 0.0f)) {
                int state = self->state;
                func_001BBCA8(self, 0);
                if (self->state != state)
                    Clear(pctl, 0x20);
            } else if (Pressed(pctl, 0x8, 0.0f)) {
                if (self->actor == D_00370AC0 && HasGadget(self->actor, 0x1B) && !func_002502F0(0.3f, self->actor)) {
                    Clear(pctl, 0x8);
                    StartGadget(self->actor, 0x1B);
                }
            }
            break;
        }
    next:
        switch (self->state) {
        case 0:
            if (g_clock.t - self->tState > 0.15f) {
                if (!(pctl->grfbtn & 0x40) && self->x3C != 3)
                    self->x24 = 1;
                func_001B77F8(self, 1, self->plo);
            } else if (!self->x2C && pctl->sLeft > 0.5f)
                func_001B8EB0(self);
            break;
        case 2:
            if (g_clock.t - self->tState > 0.15f)
                func_001B77F8(self, 3, self->plo);
            else if (!self->x2C && pctl->sLeft > 0.5f)
                func_001B8EB0(self);
            break;
        case 1:
        case 9:
            if (vel.f[2] < 0.0f)
                func_001B77F8(self, 6, self->plo);
            break;
        case 8:
            if (self->plo->x178 == 3)
                func_001B77F8(self, 6, 0);
            else if (self->actor->xf->ref < g_clock.t)
                func_001BD520(self);
            break;
        case 19: {
            float label = func_001368E0(D_0038AE90->aseg, 0x1F5);
            float t = self->actor->xf->ref;
            t -= label;
            if (t <= g_clock.t && D_0038AE90->moveState != 3) {
                func_002734E8(D_0038AE90->moverec, 3);
                break;
            }
            if (self->actor->xf->ref < g_clock.t)
                func_001BD520(self);
            break;
        }
        case 7:
            if (g_clock.t - self->tState > 0.25f && floor) {
                Leave(self->actor, 0);
                break;
            }
            if (func_001BADF8(self->tState, self->actor, &self->actor->x1408))
                func_001C0538(self->actor, 0);
            break;
        case 3:
        case 4:
        case 5:
        case 6:
            if (floor) {
                if (self->kind == 0xD)
                    func_001B40F0(self->actor->jtgrab, 10, 0, 0);
                else
                    Leave(self->actor, 0);
                break;
            }
            if (func_001BAD30(self, &self->edge)) {
                func_001B77F8(self, 18, 0);
                break;
            }
            if (func_001BADF8(self->tState, self->actor, &self->actor->x1408)) {
                func_001C0538(self->actor, 0);
                break;
            }
            if (self->actor == D_0036B250) {
                if (self->state == 3) {
                    if (g_clock.t - self->tState > 0.35f) {
                        if (pctl->grfbtn & 0x40)
                            func_001B77F8(self, 4, 0);
                        else
                            func_001B77F8(self, 5, 0);
                        break;
                    }
                }
                if (self->state == 4) {
                    if (!(pctl->grfbtn & 0x40))
                        func_001B77F8(self, 5, 0);
                }
            }
            break;
        case 18:
            if (!func_00156998(self->actor)) {
                if (g_clock.t - self->tState > 0.25f) {
                    if (func_001A7A80(pctl, 0x40, 0.25f)) {
                        func_001B7268(self, 3, 0, 0, 1.0f);
                        break;
                    }
                }
            }
            if (self->edge->plo->ptree == 0 || (self->edge->flags & 0x80000)) {
                func_001B77F8(self, 6, 0);
                break;
            }
            if (g_clock.t - self->tState > 0.03f) {
                if (!func_00176960(self->actor, &self->edge)) {
                    func_001B77F8(self, 6, 0);
                    break;
                }
            }
            func_0024E8E8(self->actor, QwScale(self->normalEdge.q, VuFloat(-1.0f)));
            if (Pressed(pctl, 0x400, 0.15f)) {
                if (HasGadget(self->actor, 3)) {
                    Clear(pctl, 0x400);
                    func_001BDA88(self->actor->jtmode, 0, 0);
                }
            }
            break;
        case 20:
            if (self->actor->x113C != 0 && !func_00138AC8(self->actor->x113C))
                break;
            func_001B77F8(self, 21, 0);
            break;
        case 21:
            if (func_0023E130(self->actor) || !(pctl->grfbtn & (func_00154798(self->actor, 0x1B) | 8)))
                func_001B77F8(self, 6, 0);
            break;
        case 22: {
            U vec;
            if (g_clock.t > self->act->tEnd) {
                ACTOR *pjt = 0;
                int saved;
                if (func_0013B500(self->actor, 0x34)) {
                    pjt = self->actor;
                    saved = pjt->x19F0;
                }
                vec.q = GetVelocity(self->actor);
                vec.f[0] = vec.f[1] = 0.0f;
                SetVelocity(self->actor, vec.q);
                func_001B7268(self, 11, 0, 0, 1.0f);
                if (pjt != 0)
                    pjt->x19F0 = saved;
                break;
            }
            if (self->placeSpot != 0 && g_clock.t + 0.25f > self->act->tEnd) {
                if (func_0013B500(self->placeObject, 0x26) || func_0013B500(self->placeObject, 10) || func_0013B500(self->placeObject, 12) ||
                    func_0013B500(self->placeObject, 0x25) || func_0013B500(self->placeObject, 11) || func_0013B500(self->placeObject, 0x20) ||
                    func_0013B500(self->placeObject, 0x7A) || func_0013B500(self->placeObject, 0x24)) {
                    func_001B7268(self, 11, 0, 0, 1.0f);
                    func_001BBCA8(self, self->placeObject);
                    break;
                }
            }
            if (self->count < self->limit && self->actor->xf->v.f[2] < 0.0f) {
                float vz = GetZ(func_001BB4E8(self, 6));
                qword pos = MatrixOf(self->actor)->r[3].q;
                qword target = func_001C9428(self->placeObject, 0, self->placePos.q);
                qword delta = QwSub(target, QwSub(pos, self->actor->offset.q));
                int n = func_0011EA28(vec.f, *(float *)(self->actor->physics + 0x88), vz, -GetZ(delta));
                int last = n - 1;
                ACTOR *player = self->actor;
                VTE &sv = player->vt[40];
                void (*fn)(void *, qword) = (void (*)(void *, qword))sv.fn;
                qword d = QwDivQ(delta, VuFloatBits(vec.i[last]).q);
                U launch;
                fn((char *)player + sv.delta, launch.q = QwFromXYZ(GFromQw(d), GetY(d), vz));
                int slot = self->count;
                self->count = slot + 1;
                void *aseg = self->asegs[slot];
                if (!aseg) aseg = self->asegD4 ? self->asegD4 : self->asegC0;
                func_00137588(aseg, self->actor, 1, &self->actor->x113C, 0.0f, 1.0f);
                self->act->tEnd = g_clock.t + vec.f[n - 1];
                func_0028B1B0(self->act->x4, self->act->x8);
                break;
            }
            if (self->placeSpot != 0 || self->placePart != 0) {
                qword posTarget = func_001C03A0(GMinOf(0.7f, self->act->tEnd - g_clock.t), self->actor, &self->placeObject);
                func_001305C8(self->act, func_0028E910(0, self->actor->xf->parent, posTarget), self->act->goalVel.q);
            }
            break;
        }
        case 10:
            if (func_002496C8(self->plo)) {
                func_001BD6C8(self);
                break;
            }
            // fall through
        case 11: case 12: case 13: case 14: case 15: case 16:
            if (self->actor->xf->ref < g_clock.t)
                func_001BD520(self);
            break;
        case 17:
            if (func_001A29B0(self->plo)) {
                func_001BD6C8(self);
                break;
            }
            if (self->actor->xf->ref < g_clock.t)
                func_001BD520(self);
            break;
        }
        if (self->state == prev)
            break;
    } while (self->state != -1);
}
