// SLY3_CFLAGS: -Os -G0 -ffast-math
// Per-frame update of the Sly 3 character controller's state machine (states 0..6, see func_001F6148 for the
// setter): decide the next state from the owner's input; repeat until the state is stable; then keep the owner's
// lock-on updated for the final state.
#include "deferred_callback_api.h"
typedef int qword __attribute__((mode(TI)));
struct PO { char pad0[8]; float g8; };
struct X11D0 { char pad[0x68]; int x68; };
struct OWNER {
    char pad0[0x134]; struct PO *po; char pad138[0x190 - 0x138]; float f190; char pad194[0x218 - 0x194];
    int x218; char pad21C[0x107C - 0x21C]; int x107C; char pad1080[0x1144 - 0x1080]; int x1144;
    char pad1148[0x11C8 - 0x1148]; void *x11C8; unsigned int x11CC; struct X11D0 *x11D0;
};
struct SELF { char pad0[0x10]; struct OWNER *owner; char pad14[0x30 - 0x14]; int state; float stamp; void *p38; };
extern unsigned char D_00475480[];
extern struct DEFERRED_PMF D_00325490;
extern qword D_00317560;
void func_002389A0(struct SELF *);
int func_001A7A80(struct PO *, int, float);
void func_001528E0(void *);
int func_00238AD0(struct SELF *);
int func_001F6300(struct SELF *);
void *func_001A29B0(void *);
void func_001F5C58(struct SELF *);
void func_001F5CC8(struct SELF *);
int func_002503C8(struct OWNER *, float);
void func_00256828(struct OWNER *, struct X11D0 *, int, qword);
void func_001F6148(struct SELF *, int, void *);
void func_00257D78(struct OWNER *, int);

void func_001F5D70(struct SELF *self)
{
    int s;
    struct PO *po;
    func_002389A0(self);
    if (func_001A7A80(self->owner->po, 0x200, 0.0f))
        func_001528E0(self->p38);
    do {
        s = self->state;
        switch (s) {
        case 0:
            if (func_00238AD0(self))
                func_001F6148(self, 1, 0);
            break;
        case 1:
        case 2:
            po = self->owner->po;
            if (func_001F6300(self)) {
                func_0015DC68(D_00475480, self->owner, D_00325490, 0);
            } else if (!self->p38 && func_001A29B0(self->owner->x11C8)) {
                self->p38 = func_001A29B0(self->owner->x11C8);
                func_001F5C58(self);
            } else if (self->owner->x11CC != 1 && func_001A7A80(po, 0x10, 0.15f)) {
                func_001F5CC8(self);
            } else if ((self->owner->x1144 & 0x10) && func_001A7A80(po, 0x40, 0.15f) &&
                       (self->owner->x218 || !func_002503C8(self->owner, 0.1f))) {
                func_001F6148(self, 3, 0);
            } else if (self->owner->x11D0 && !self->owner->x107C && func_001A7A80(po, 0x80, 0.15f)) {
                if (self->owner->x11D0->x68)
                    func_00256828(self->owner, self->owner->x11D0, 0, D_00317560);
                else
                    func_001F6148(self, 5, 0);
            } else if (self->owner->x11CC < 2 || self->owner->x11CC == 3) {
                func_001F6148(self, 2, 0);
            } else if (po->g8 == 0.0f) {
                func_001F6148(self, 1, 0);
            } else {
                func_001F6148(self, 2, 0);
            }
            break;
        case 6:
            if (func_00238AD0(self))
                func_001F6148(self, 2, 0);
            break;
        case 3:
        case 4:
            po = self->owner->po;
            if (func_00238AD0(self)) {
                func_001F6148(self, 2, 0);
            } else if (func_001F6300(self)) {
                func_0015DC68(D_00475480, self->owner, D_00325490, 0);
            } else if (self->owner->x11CC != 1 && func_001A7A80(po, 0x10, 0.15f)) {
                func_001F5CC8(self);
            }
            break;
        case 5:
            if (func_00238AD0(self))
                func_001F6148(self, 2, 0);
            break;
        }
    } while (s != self->state);
    switch (self->state) {
    case 2:
        self->owner->f190 = 1.0f;
        func_00257D78(self->owner, self->p38 != 0);
        break;
    case 5:
    case 6:
        func_00257D78(self->owner, self->p38 != 0);
        break;
    case 0:
    case 1:
    case 3:
    case 4:
        break;
    }
}
