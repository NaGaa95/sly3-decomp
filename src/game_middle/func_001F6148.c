// SLY3_CFLAGS: -Os -G0
// SLY3_AS: gnu-2.9
/* State setter: start the per-state animation record for the new state (owns the jump table at 0x3254E0). */
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta; short pad; void *(*method)(void *); };
struct REC { char pad[0xC]; struct VTE *vt; char pad10[0x30 - 0x10]; char *x30; char *x34; char pad38[0x3C - 0x38]; int x3C;
    char pad40[0xCC - 0x40]; int xCC; char padD0[0xF4 - 0xD0]; float xF4; char padF8[0xFC - 0xF8]; float xFC; };
struct OWNER { char pad[0x29C]; char list[0x11D0 - 0x29C]; char *p11D0; };
struct SELF { char pad[0x10]; struct OWNER *owner; char pad14[0x18 - 0x14]; char slot[0x30 - 0x18]; int state; float stamp; };
struct POSE { qword pos; float x10; float x14; };
extern struct CLOCK { float t; } g_clock;
void func_00238AE8(void *slot);
void func_00238AB8(void *self);
struct REC *func_00238690(void *list, int kind);
void func_00132930(struct REC *, qword);
void func_002BC760(void *, void *);
#define VCALL(po, n) ((po)->vt[n].method((char *)(po) + (po)->vt[n].delta))

void func_001F6148(struct SELF *self, int state, struct POSE *pose)
{
    if (state == self->state)
        return;
    func_00238AE8(self->slot);
    self->state = state;
    self->stamp = g_clock.t;
    switch (state) {
    case 0: {
        struct REC *rec = func_00238690(self->owner->list, 0xC9);
        rec->x3C = 0x11;
        VCALL(rec, 8);
        break;
    }
    case 1: {
        struct REC *rec = func_00238690(self->owner->list, 0xCA);
        VCALL(rec, 8);
        break;
    }
    case 5: {
        struct REC *rec = func_00238690(self->owner->list, 0xCC);
        rec->x34 = self->owner->p11D0 + 0xB0;
        VCALL(rec, 8);
        break;
    }
    case 3: {
        struct REC *rec = func_00238690(self->owner->list, 0xCB);
        rec->xCC = 5;
        VCALL(rec, 8);
        break;
    }
    case 4: {
        struct REC *rec = func_00238690(self->owner->list, 0xCB);
        rec->xCC = 4;
        func_00132930(rec, pose->pos);
        rec->xFC = pose->x10;
        rec->xF4 = pose->x14;
        VCALL(rec, 8);
        break;
    }
    case 2: {
        struct REC *rec = func_00238690(self->owner->list, 0xC9);
        rec->x3C = 0xE;
        VCALL(rec, 8);
        break;
    }
    case 6: {
        struct REC *rec = func_00238690(self->owner->list, 0xCE);
        func_002BC760(&rec->x30, pose);
        VCALL(rec, 8);
        break;
    }
    case -1:
        func_00238AB8(self);
        break;
    }
}
