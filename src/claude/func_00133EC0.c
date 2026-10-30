// SLY3_CFLAGS: -Os -G0
/* State setter: start the per-state animation records (owns jump table 0x31F7F0). */
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta; short pad; void *(*method)(void *); };
struct REC { char pad[0xC]; struct VTE *vt; char pad10[0x30 - 0x10]; int x30; char pad34[0x38 - 0x34]; int x38; int x3C;
    char pad40[0xCC - 0x40]; int xCC; };
struct OBJ { char pad[0xC]; struct VTE *vt; };
struct POS { char pad[0x30]; qword pos; };
struct ENT { int x0; struct OBJ **ppo; };
struct PATH { int x0; int c; struct ENT *ae; };
struct OWNER { char pad[0x29C]; char list[0x1764 - 0x29C]; struct PATH *ppath; };
struct SELF { char pad[0x10]; struct OWNER *owner; char pad14[0x18 - 0x14]; char slot[0x30 - 0x18]; int state; float stamp;
    float g38; char pad3C[0x44 - 0x3C]; int i44; int x48; };
extern struct CLOCK { float t; } g_clock;
extern const float D_0031F878[2];
void func_00238AE8(void *slot);
void func_00238AB8(void *self);
struct REC *func_00238690(void *list, int kind);
void func_00257F18(struct OWNER *, int);
float func_0011E940(float, float);
void func_00132930(struct REC *, qword);
#define VCALL(po, n) ((po)->vt[n].method((char *)(po) + (po)->vt[n].delta))

void func_00133EC0(struct SELF *self, int state, int x)
{
    if (state == self->state)
        return;
    func_00238AE8(self->slot);
    self->state = state;
    self->stamp = g_clock.t;
    switch (state) {
    case 0: {
        struct REC *rec = func_00238690(self->owner->list, 0xED);
        self->i44 = 0;
        self->x48 = 0;
        rec->x38 = (int)*self->owner->ppath->ae[0].ppo;
        VCALL(rec, 8);
        func_00257F18(self->owner, 0);
        break;
    }
    case 1: {
        struct REC *rec = func_00238690(self->owner->list, 0xCA);
        VCALL(rec, 8);
        break;
    }
    case 2: {
        struct REC *rec = func_00238690(self->owner->list, 0xEC);
        rec->x38 = x;
        VCALL(rec, 8);
        func_00257F18(self->owner, 1);
        {
            float t = g_clock.t;
            self->g38 = t + func_0011E940(D_0031F878[0], D_0031F878[1]);
        }
        break;
    }
    case 3: {
        struct OBJ *po;
        struct REC *rec = func_00238690(self->owner->list, 0xCB);
        rec->xCC = 1;
        self->i44 = (self->i44 + 1) % self->owner->ppath->c;
        self->x48 = 0;
        po = *self->owner->ppath->ae[self->i44].ppo;
        func_00132930(rec, ((struct POS *)VCALL(po, 36))->pos);
        VCALL(rec, 8);
        func_00257F18(self->owner, 0);
        break;
    }
    case 4: {
        struct REC *rec = func_00238690(self->owner->list, 0xC9);
        rec->x3C = 0x22;
        VCALL(rec, 8);
        break;
    }
    case 5: {
        struct REC *rec = func_00238690(self->owner->list, 0xF1);
        rec->x30 = x;
        VCALL(rec, 8);
        func_00257F18(self->owner, 1);
        break;
    }
    case 6: {
        struct REC *rec = func_00238690(self->owner->list, 0xCA);
        rec->x3C = 1;
        VCALL(rec, 8);
        break;
    }
    case -1:
        func_00238AB8(self);
        break;
    }
}
