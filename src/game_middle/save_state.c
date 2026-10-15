// SLY3_CFLAGS: -Os -G0
// Save-state transition; Sly 2 supplies the algorithm, Sly 3 supplies the layout.
struct PMF {
    short delta, pad;
    int (*pfn)(void *);
};
struct S {
    int x0, x4;
    struct PMF pmf;
    int x10;
};
typedef char method_size8[(sizeof(struct PMF) == 8) ? 1 : -1];
typedef char context_size20[(sizeof(struct S) == 20) ? 1 : -1];
#include "save_state_api.h"
struct SaveStateView {
    char unaccessed0[8];
    int state;
    char unaccessedC[4];
    float state_time;
    char unaccessed[0x13950 - 0x14];
    unsigned int word13950;
    void *selected_record;
    char unaccessed13958[8];
    struct S thread_context;
};
struct StatusView {
    char unaccessed[0x58];
    int state;
};
extern struct StatusView D_003751D0;
extern char D_00375240[];
struct ClockView {
    char unaccessed[0x40];
    float value;
};
extern struct ClockView D_0036BB98;
extern const struct PMF D_003239F0, D_003239F8;
void func_001D0D30(void *, int);
int func_001D2138(void *);
void func_001D0C08(void *, int);
void func_001D2100(void *);
void func_001CEEC0(struct S *, struct PMF);
void func_001CF578(void *);
void func_001CF430(void *receiver, int state) {
    struct SaveStateView *save = receiver;
    if (state == save->state) return;
    if (save->state == 6) {
        save->selected_record = 0;
        if (save->word13950) {
            struct StatusView *status = &D_003751D0;
            if (status->state == 1) {
                func_001D0D30(status, 3);
                if (func_001D2138(D_00375240)) {
                    func_001D0C08(status, 0x30);
                    func_001D2100(D_00375240);
                }
                else {
                    func_001D0C08(status, 0x31);
                }
            }
        }
    }
    switch (state) {
        case 0: case 1: func_001CEEC0(&save->thread_context, D_003239F0);
        break;
        case 3: func_001CEEC0(&save->thread_context, D_003239F8);
        break;
        case 6: func_001CF578(save);
        break;
    }
    save->state = state;
    save->state_time = D_0036BB98.value;
}
