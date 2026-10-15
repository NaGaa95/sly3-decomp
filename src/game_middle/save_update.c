// Save updater recovered from the full original ordered control flow.
// SLY3_CFLAGS: -Os -G0
// Save updater; actual Sly 3 ordered time checks and notification modes.
#include "save_state_api.h"
struct PMF { short delta, pad; int (*pfn)(void *); };
struct S { int x0, x4; struct PMF pmf; int x10; };
typedef char method_size8[(sizeof(struct PMF) == 8) ? 1 : -1];
typedef char worker_size20[(sizeof(struct S) == 20) ? 1 : -1];
struct SaveUpdateView {
    char unaccessed0[8];
    int state, desired_state;
    float state_time, poll_time;
    char unaccessed18[0x13960 - 0x18];
    struct S thread_context;
};
struct StatusView {
    char unaccessed[0x50];
    int mode;
    float mode_time;
    int state;
};
struct ClockView { char unaccessed[0x40]; float value; };
extern struct StatusView D_003751D0;
extern struct ClockView D_0036BB98;
extern char D_00475480[], D_00389AC0[], D_0046F550[];
extern unsigned int D_0036DBA8, D_0046FC84;
extern const struct PMF D_003239F0;
int func_0025AE28(void *);
int func_001CEFB8(void *);
void func_001CEEC0(struct S *, struct PMF);
void func_001CF640(void *, int);
int func_001DC520(void *);
int func_001D4738(void *);
int func_0021DD30(void *);
void func_001D0C08(void *, int);

void func_001CF0D0(void *receiver)
{
    struct SaveUpdateView *save = receiver;
    if (func_0025AE28(D_00475480))
        return;
    if (D_0036DBA8)
        return;
    if (D_003751D0.state == 3)
        return;
    if (func_001CEFB8(&save->thread_context))
        return;
    if (save->state == save->desired_state) {
        if (save->poll_time <= D_0036BB98.value)
            func_001CEEC0(&save->thread_context, D_003239F0);
        else
            func_001CF640(save, 0);
    } else {
        func_001CF430(save, save->desired_state);
    }
    if (func_001CEFB8(&save->thread_context))
        return;
    if (func_001DC520(D_00389AC0))
        return;
    if (D_003751D0.state != 1)
        return;
    if (0.3f <= D_0036BB98.value - save->state_time) {
        if (func_001D4738(D_0046F550)) {
            if (save->state == 1)
                func_001D0C08(&D_003751D0, 0x1C);
            else if (save->state != 6)
                func_001D0C08(&D_003751D0, 0x3B);
            return;
        }
        switch (save->state) {
        case 1:
            if (D_0046FC84) {
                func_001D0C08(&D_003751D0, 0x1A);
            } else {
                if (func_0021DD30(&D_003751D0)) {
                    if (D_003751D0.mode == 0x3F &&
                        D_0036BB98.value - D_003751D0.mode_time <= 2.0f)
                        return;
                }
                func_001D0C08(&D_003751D0, 0x1B);
            }
            break;
        case 2:
            func_001D0C08(&D_003751D0, 0x1D);
            break;
        case 3:
            func_001D0C08(&D_003751D0, 0x20);
            break;
        case 4:
            if (D_0046FC84) {
                func_001D0C08(&D_003751D0, 0x23);
            } else {
                if (func_0021DD30(&D_003751D0)) {
                    if (D_003751D0.mode == 0x3E &&
                        D_0036BB98.value - D_003751D0.mode_time <= 2.0f)
                        return;
                }
                func_001D0C08(&D_003751D0, 0x24);
            }
            break;
        }
    }
}
