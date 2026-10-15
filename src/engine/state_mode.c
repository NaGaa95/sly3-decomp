// SLY3_CFLAGS: -Os -G0
#include "resource_attachment_api.h"
#include "owned_record_list_api.h"

struct Clock { float time, step; };
extern struct Clock D_0036BB98;
struct VirtualEntry {
    short adjustment, reserved;
    void (*method)(void *);
};
struct Command {
    char prefix[0xC];
    struct VirtualEntry *table;
    char opaque10[0x2C];
    int mode3C;
};
struct Owner {
    char prefix[0x35C];
    int enabled35C;
};
struct State {
    char prefix[0x10];
    struct Owner *owner10;
    int word14;
    char retained18[0x18];
    int mode30;
    float changed34;
};
void func_00238A38(void *receiver);
void func_00238AB8(void *receiver);

void func_0016D840(void *receiver, int mode) {
    struct State *state = receiver;
    if (state->mode30 == mode) return;
    func_00238AE8(state->retained18);
    state->mode30 = mode;
    state->changed34 = D_0036BB98.time;
    switch (mode) {
    case 0: case 1: case 2: case 3: case 4: {
        struct Command *command = func_00238690((char *)state->owner10 + 0x29C, 0xC9);
        int modes[5] = {37, 38, 39, 40, 38};
        struct VirtualEntry *entry;
        command->mode3C = modes[state->mode30];
        entry = command->table + 8;
        entry->method((char *)command + entry->adjustment);
        state->owner10->enabled35C = (unsigned)state->mode30 < 2;
        break;
    }
    case -1:
        func_00238A38(state);
        func_00238AB8(state);
        state->owner10->enabled35C = 0;
        break;
    }
}
