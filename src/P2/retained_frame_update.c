// Retained-state frame update, including the Sly3 explicit fade.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct X;
struct Q {
    char pad[0x3C];
    struct Q *next3C;
};
#include "approach_curve.h"
#include "retained_frame_api.h"
struct P {
    char pad0[0x4C];
    struct Q *head4C;
    char pad50[8];
    int active58;
    char pad5C[0x140 - 0x5C];
    float current140;
    char pad144[0x160 - 0x144];
    float scale160;
    char pad164[0x1D4 - 0x164];
    float target1D4;
    struct ApproachCurve fade1D8;
    char pad1E4[0x200 - 0x1E4];
    unsigned long time200, previous208;
    struct X *owner210;
    int count214;
    struct X *entries218[8];
    struct X *last238;
};
struct CLOCK {
    float t, dt;
    char pad[0x44 - 8];
    float elapsed44;
    char pad48[8];
    unsigned long previousCount50;
    unsigned int wraps58;
};
typedef char CheckLong64[(sizeof(unsigned long) == 8) ? 1 : -1];
typedef char CheckCurve12[(sizeof(struct ApproachCurve) == 12) ? 1 : -1];
typedef char CheckNodePrefix40[(sizeof(struct Q) == 0x40) ? 1 : -1];
typedef char CheckFramePrefix240[(sizeof(struct P) == 0x240) ? 1 : -1];
typedef char CheckClockPrefix60[(sizeof(struct CLOCK) == 0x60) ? 1 : -1];
extern struct CLOCK D_0036BB98;
extern int D_003440C0;
extern const struct ApproachCurve D_00326EA8;
extern const float D_00326EB4;
unsigned long func_001655B0(struct CLOCK *);
void func_002479C8(struct P *);
void func_00247B38(struct P *);
void func_00244C70(struct X *);
void func_00244C28(struct X *);
void func_00247B98(struct P *);
void func_00247EC8(struct P *);
int func_002485C0(struct P *);
#include "gain_control_api.h"
void func_00245748(struct Q *);
int func_002908F0(void);
void func_00247728(struct P *p) {
    struct X *top;
    float f, g;
    struct ApproachCurve curve;
    struct Q *q;
    p->previous208 = p->time200;
    p->time200 = func_001655B0(&D_0036BB98);
    func_002479C8(p);
    func_00247B38(p);
    top = p->count214 > 0 ? *(p->entries218 + p->count214 - 1) : 0;
    if (D_003440C0 == 3) {
        if (p->active58) {
            if (top) func_00244C70(top);
            if (p->last238) func_00244C70(p->last238);
            if (p->owner210) func_00244C70(p->owner210);
            p->active58 = 0;
        }
    }
    else if (!p->active58) {
        if (top) func_00244C28(top);
        if (p->last238) func_00244C28(p->last238);
        if (p->owner210) func_00244C28(p->owner210);
        p->active58 = 1;
    }
    func_00247B98(p);
    func_00247EC0(p);
    func_00247EC8(p);
    if (p->target1D4 != D_00326EB4) {
        float fade = func_0011E598(p->current140, p->target1D4, &p->fade1D8, 0, D_0036BB98.dt);
        if (fade == p->target1D4) p->target1D4 = D_00326EB4;
        func_00248A78(p, 0, fade, 0);
        func_00248A78(p, 1, fade, 0);
        func_00248A78(p, 2, fade, 0);
    }
    curve = D_00326EA8;
    g = (func_002485C0(p) && D_0036BB98.dt == 0.0f) ? 0.0f : 1.0f;
    f = func_0011E598(p->scale160, g, &curve, 0, D_0036BB98.elapsed44);
    func_00248A78(p, 0, f, 2);
    func_00248A78(p, 1, f, 2);
    func_00248A78(p, 2, g, 2);
    for (q = p->head4C; q;) {
        struct Q *next = q->next3C;
        func_00245748(q);
        q = next;
    }
    func_002908F0();
}
