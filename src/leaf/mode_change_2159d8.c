// Switch the object to a new mode: leave the old mode (release the tracked effect of modes 2/4, clear the 0x200 flag of mode 3), stamp the time, fetch the new goal, apply the per-mode entry work (flag/hook for 3, slot restart for 5, zero motion for 0/1/6, notification for 7), retune the slot types and tell the listener its sound id.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta, pad; void *fn; };
struct Slot { unsigned char pad0[0x10]; int type; unsigned char pad14[0x1C - 0x14]; };
struct Obj { unsigned char pad0[0xC]; struct VTE *pvt; };
struct Ref { void *obj; int id; int state; };
struct Self {
    unsigned char pad0[0xC]; struct VTE *pvt;
    unsigned char pad10[0x3C - 0x10]; int flags;
    unsigned char pad40[0x48 - 0x40]; void *n48; unsigned char pad4C[4]; void *n50;
    unsigned char pad54[0x130 - 0x54]; int n130;
    unsigned char pad134[0x148 - 0x134]; void *p148;
    unsigned char pad14C[0x1B0 - 0x14C]; int mode; float enterTime; int phase;
    unsigned char pad1BC[0x1DC - 0x1BC]; void *goal;
    unsigned char pad1E0[0x22C - 0x1E0]; float g22C;
    unsigned char pad230[0x270 - 0x230]; struct Slot slots[2][6];
    int counts[2];
    unsigned char pad3C8[0x414 - 0x3C8]; void *listener;
    unsigned char pad418[0x444 - 0x418]; void *p444; struct Obj *p448;
    unsigned char pad44C[0x548 - 0x44C]; struct Ref ref548;
};
struct CLOCK { float now; };
extern struct CLOCK D_0036BB98;
extern unsigned char D_00475480[];
extern unsigned char D_0036C700[];
extern qword D_00317560;
extern int D_00325BC0[];
extern float D_00325BE0;
void func_001F47C8(struct Self *, void *);
void func_001A94F0(void *, int);
void func_001A94A8(void *, int);
void func_00240DB0(struct Self *);
void func_00244CA8(void *, float);
void func_002BBCD8(struct Ref *, void *);
void *func_002151A0(struct Self *, int);
void func_00215F10(struct Self *, int);
void func_00219210(struct Self *);
void func_00217D50(struct Self *, struct Slot *, int, float);
void func_0028F068(struct Self *, void *, int);
void func_0023EC98(struct Self *, int);
void func_0023EBF8(struct Self *, int);
void func_00215958(struct Self *);
void func_00239DB8(void *, int);
void func_001854C8(void *, int, struct Self *);
void func_002159D8(struct Self *self, int mode)
{
    int i, j;
    if (self->mode == mode)
        return;
    if (self->p444) {
        int wasMove = (unsigned)(self->mode - 2) < 2;
        int isMove = (unsigned)(mode - 2) < 2;
        if (wasMove != isMove) {
            if (isMove) {
                func_001F47C8(self, self->p444);
            } else {
                if (self->p148 == self->p444)
                    func_001F47C8(self, 0);
            }
        }
    }
    switch (self->mode) {
    case 3:
        func_001A94F0(D_00475480, self->n130);
        if (self->p448) {
            struct VTE *e = &self->p448->pvt[54];
            ((void (*)(void *))e->fn)((char *)self->p448 + e->delta);
            {
                int v = self->flags;
                if ((v ^ 1) & 1)
                    *(int *)v &= ~0x200;
                else
                    self->flags = v & ~0x200;
            }
        }
        break;
    case 7:
        func_00240DB0(self);
        break;
    }
    if (self->mode == 2 || self->mode == 4) {
        struct Ref *ref = &self->ref548;
        if (ref->obj) {
            func_00244CA8(ref->obj, 0.0f);
            func_002BBCD8(ref, 0);
        }
    }
    self->mode = mode;
    self->enterTime = D_0036BB98.now;
    self->goal = func_002151A0(self, mode);
    if (self->phase != 2) {
        switch (self->mode) {
        case 2:
            func_00215F10(self, 0);
            break;
        case 4:
            func_00215F10(self, 1);
            break;
        default:
            func_00215F10(self, -1);
            break;
        }
    }
    self->g22C = 0.0f;
    switch (self->mode) {
    case 3:
        func_001A94A8(D_00475480, self->n130);
        if (self->p448) {
            int v = self->flags;
            if ((v ^ 1) & 1)
                *(int *)v |= 0x200;
            else
                self->flags = v | 0x200;
            {
                struct VTE *e = &self->p448->pvt[56];
                ((void (*)(void *))e->fn)((char *)self->p448 + e->delta);
            }
            func_00219210(self);
        }
        break;
    case 5:
        for (i = 0; i < 2; i++) {
            for (j = 0; j < self->counts[i]; j++)
                func_00217D50(self, &self->slots[i][j], 4, D_00325BE0);
        }
        break;
    case 0:
    case 1:
    case 6: {
        struct VTE *e = &self->pvt[40];
        ((void (*)(void *, qword))e->fn)((char *)self + e->delta, D_00317560);
        e = &self->pvt[41];
        ((void (*)(void *, qword))e->fn)((char *)self + e->delta, D_00317560);
        break;
    }
    case 7:
        if (self->phase == 2)
            func_001854C8(D_0036C700, 0x10, self);
        else
            func_001854C8(D_0036C700, 0xC, self);
        break;
    }
    switch (self->mode) {
    case 2:
    case 3:
    case 4:
    case 5:
        func_0028F068(self, self->n48, 2);
        func_0028F068(self, self->n50, 2);
        func_0023EC98(self, 4);
        func_0023EBF8(self, 5);
        break;
    default:
        func_0028F068(self, self->n48, 1);
        func_0028F068(self, self->n50, 1);
        func_0023EC98(self, 1);
        func_0023EBF8(self, 1);
        break;
    }
    func_00215958(self);
    if (self->mode == 1 || self->mode == 4) {
        for (i = 0; i < 2; i++) {
            int n = self->counts[i];
            for (j = 0; j < n; j++) {
                struct Slot *slot = &self->slots[i][j];
                if (slot->type == 0)
                    func_00217D50(self, slot, 1, D_00325BE0);
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            int n = self->counts[i];
            for (j = 0; j < n; j++) {
                struct Slot *slot = &self->slots[i][j];
                if (slot->type != 4)
                    func_00217D50(self, slot, 0, D_00325BE0);
            }
        }
    }
    if (self->listener && self->mode >= 0)
        func_00239DB8(self->listener, D_00325BC0[self->mode]);
}
