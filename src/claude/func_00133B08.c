// SLY3_CFLAGS: -Os -G0
/* State update for the func_00133EC0 state machine (owns PMF 0x31F7C0 and jump table 0x31F7D0). */
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta; short pad; void *(*method)(void *); };
struct OBJ { char pad[0xC]; struct VTE *vt; };
struct POS { float f0, f4; };
struct POSQ { char pad[0x30]; qword pos; };
static inline float Z(qword q) { float f; __asm__("pextuw %0, $0, %1" : "=r"(f) : "r"(q)); return f; }
struct ENT { int c; struct OBJ **apo; };
struct PATH { int x0; int c; struct ENT *ae; };
struct OWNER { char pad[0xC]; struct VTE *vt; char pad10[0x1764 - 0x10]; struct PATH *ppath; };
struct REC { char pad[0x30]; int x30; char pad34[0x38 - 0x34]; int x38; };
struct R40 { char pad[0x40]; void *p40; };
struct SELF { char pad[0x10]; struct OWNER *owner; char pad14[0x18 - 0x14]; struct REC *prec; char pad1C[0x30 - 0x1C];
    int state; float stamp; float g38; char pad3C[0x44 - 0x3C]; int i44; int x48; };
struct DEFERRED_PMF { short delta, index; union { void (*direct)(void *, void *); short vptrOffset; int word; } target; };
extern struct CLOCK { float t; } g_clock;
extern const float D_0031F878[2];
extern unsigned char D_00475480[];
void func_002389A0(struct SELF *);
int func_00254B80(struct OWNER *);
void *func_001342B8(struct SELF *);
int func_00134148(struct SELF *, void *);
int func_00134200(struct SELF *, int);
void func_00133EC0(struct SELF *, int, int);
struct R40 *func_00256090(struct OWNER *, int);
void func_0024E920(struct OWNER *, void *);
float func_002A3EE8(float, float);
void func_0024E878(struct OWNER *, float);
float func_0011E940(float, float);
int func_00238AD0(struct SELF *);
void func_001355C8(struct REC *, int);
void func_0015DC68(void *game, void *receiver, struct DEFERRED_PMF member, void *owner);
void func_00133E78(void *, void *);
#define VCALL(po, n) ((po)->vt[n].method((char *)(po) + (po)->vt[n].delta))

void func_00133B08(struct SELF *self)
{
    static const struct DEFERRED_PMF pmf = { 0, -1, { func_00133E78 } };
    int state;
    func_002389A0(self);
    do {
        state = self->state;
        switch (state) {
        case 1: {
            void *p;
            if (func_00254B80(self->owner)) {
                func_00133EC0(self, 6, 0);
                break;
            }
            p = func_001342B8(self);
            if (p) {
                if (func_00134148(self, p))
                    func_00133EC0(self, 5, (int)p);
                else
                    func_00133EC0(self, 2, (int)p);
                break;
            }
            {
                struct R40 *pr = func_00256090(self->owner, 0);
                if (pr && pr->p40) {
                    func_0024E920(self->owner, pr->p40);
                    break;
                }
            }
            {
                struct OBJ *po = self->owner->ppath->ae[self->i44].apo[self->x48];
                struct POS *pp = (struct POS *)VCALL(po, 36);
                func_0024E878(self->owner, func_002A3EE8(pp->f4, pp->f0));
            }
            {
                float t = g_clock.t;
                if (self->g38 <= t) {
                    self->g38 = t + func_0011E940(D_0031F878[0], D_0031F878[1]);
                    self->x48 = (self->x48 + 1) % self->owner->ppath->ae[self->i44].c;
                }
            }
            if (g_clock.t - self->stamp > 20.0f) {
                if (self->i44 >= self->owner->ppath->c - 1)
                    func_00133EC0(self, 4, 0);
                else
                    func_00133EC0(self, 3, 0);
            }
            break;
        }
        case 2: {
            struct REC *prec;
            if (func_00254B80(self->owner)) {
                func_00133EC0(self, 6, 0);
                break;
            }
            prec = self->prec;
            if (func_00238AD0(self)) {
                func_00133EC0(self, 1, 0);
                break;
            }
            if (func_00134148(self, (void *)prec->x38))
                func_00133EC0(self, 5, prec->x38);
            break;
        }
        case 5: {
            struct REC *prec = self->prec;
            if (func_00238AD0(self)) {
                if (func_00254B80(self->owner)) {
                    func_00133EC0(self, 6, 0);
                    break;
                }
                func_00133EC0(self, 2, prec->x30);
                break;
            }
            if (func_00134200(self, prec->x30) || func_00254B80(self->owner))
                func_001355C8(prec, 3);
            break;
        }
        case 0:
        case 3:
            if (func_00238AD0(self))
                func_00133EC0(self, 1, 0);
            break;
        case 4: {
            struct POSQ *pq = (struct POSQ *)VCALL((struct OBJ *)self->owner, 36);
            if (Z(pq->pos) > 8000.0f)
                func_0015DC68(D_00475480, self, pmf, 0);
            break;
        }
        case 6:
            if (!func_00254B80(self->owner))
                func_00133EC0(self, 1, 0);
            break;
        }
    } while (state != self->state);
}
