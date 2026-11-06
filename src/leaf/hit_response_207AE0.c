// SLY3_CFLAGS: -Os -G0 -ffast-math
struct VTE { short d; short pad; int (*fn)(void *, int); };
struct VT { char pad[0x280]; struct VTE e80; };
struct Link { char pad[0x14]; int id; };
struct Target { char pad[0x1E8]; struct Link *link; };
struct Event {
    char pad0[0x14]; struct Target *target; char pad18[8]; int n20; int n24; int n28;
    char pad2C[0x50 - 0x2C]; unsigned int flags;
};
struct Self {
    char pad0[0xC]; struct VT *vt; int pad10; int id14; char pad18[0x130 - 0x18]; int n130;
    char pad134[0x380 - 0x134]; int n380; char pad384[0x398 - 0x384]; float g398; float g39C;
};
extern float D_00325870;
extern char D_0036C700[];
extern char D_0036BD20[];
extern char D_0036E740[];
int func_0013B500(void *, int);
void func_001F4DD8(struct Self *, struct Target *, int, float);
int func_001F43D0(struct Self *, int);
int func_001F43F0(struct Self *);
int func_001F43C8(struct Self *);
float func_00171C98(void *);
int func_002047D0(struct Self *, int);
int func_001F4350(struct Self *, int);
void func_001A9058(void *, int, float);
void *func_001F4A80(struct Self *);
void func_00167D38(void *, int);
void func_001854C8(void *, int, struct Self *);
int func_00207AE0(struct Self *self, struct Event *ev)
{
    int heavy;
    int amount, cap;
    if (self->vt->e80.fn((char *)self + self->vt->e80.d, ev->n20))
        return 0;
    if (!(ev->flags & 2))
        return 0;
    if (func_0013B500(ev->target, 0x59)) {
        if (ev->target->link->id == self->id14)
            return 0;
    }
    heavy = 0;
    func_001F4DD8(self, ev->target, ev->n20, D_00325870);
    if (ev->n20 == 0x2000 || ev->n20 == 0x4000)
        heavy = 1;
    if (ev->n28 || (self->n380 != 1 && heavy)) {
        func_001F43D0(self, 0);
    } else {
        amount = (int)((float)func_001F43F0(self) * 0.05f);
        cap = (int)((float)ev->n24 * (1.0f - func_00171C98(D_0036BD20)));
        if (cap >= amount)
            amount = cap;
        func_001F43D0(self, func_001F43C8(self) - amount);
    }
    if (func_001F43C8(self) > 0 && heavy && self->n380 == 1 && !func_002047D0(self, 1))
        func_001F43D0(self, 0);
    if (func_001F4350(self, -1)) {
        func_001A9058(D_0036E740 + self->n130 * 0x11C0, 4, 0.75f);
        func_00167D38(func_001F4A80(self), 0);
        if (func_001F43C8(self) > 0) {
            func_001854C8(D_0036C700, 0xA, self);
            self->g39C = self->g398;
        } else {
            func_001854C8(D_0036C700, 0xC, self);
        }
    } else {
        if (func_001F43C8(self) > 0)
            func_001854C8(D_0036C700, 0xF, self);
        else
            func_001854C8(D_0036C700, 0x10, self);
    }
    return 1;
}
