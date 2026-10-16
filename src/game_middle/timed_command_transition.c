// SLY3_CFLAGS: -Os -G0
#include "resource_attachment_api.h"
#include "owned_record_list_api.h"
struct CLOCK { float t, dt; };
extern struct CLOCK D_0036BB98;
extern float D_00324E64;
struct TimedCommandVirtualEntry { short delta, reserved; void (*call)(void *); };
struct TimedCommandObject {
    char prefix[0xC];
    struct TimedCommandVirtualEntry *table;
    char reserved10[0x3C - 0x10];
    int mode;
};
struct TimedCommandTransition {
    char prefix[0x10];
    char *owner;
    int word14;
    void *retained;
    char reserved1C[0x30 - 0x1C];
    float first_deadline, second_deadline;
    int state;
    float state_time;
    void *program;
};
void func_001982C8(void *command, void *result);
void func_00197838(void *command, void *program, int value, void *parameters);
void func_001EFC88(void *receiver);
void func_001EFC10(void *receiver);

void func_001EFAB8(void *receiver, int state)
{
    struct TimedCommandTransition *p = receiver;
    if (state == p->state) return;
    if (p->state == 0) func_001982C8(p->retained, p->owner + 0x318);
    func_00238AE8(&p->retained);
    p->state = state;
    p->state_time = D_0036BB98.t;
    switch (state) {
    case 1:
    case 2:
        {
            struct TimedCommandObject *command = func_00238690(p->owner + 0x29C, 0xCA);
            struct TimedCommandVirtualEntry *entry = &command->table[8];
            entry->call((char *)command + entry->delta);
        }
        func_001EFC88(receiver);
        p->first_deadline = D_00324E64;
        break;
    case 0:
        {
            struct TimedCommandObject *command = func_00238690(p->owner + 0x29C, 0xD3);
            struct TimedCommandVirtualEntry *entry;
            func_00197838(command, p->program, 0, p->owner + 0x318);
            entry = &command->table[8];
            entry->call((char *)command + entry->delta);
        }
        func_001EFC10(receiver);
        p->second_deadline = D_00324E64;
        break;
    case 3:
        {
            struct TimedCommandObject *command = func_00238690(p->owner + 0x29C, 0xCA);
            struct TimedCommandVirtualEntry *entry;
            command->mode = 1;
            entry = &command->table[8];
            entry->call((char *)command + entry->delta);
        }
        break;
    }
}
