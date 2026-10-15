// Complete original function, inputs and emitted data independently reviewed.
// PRIVATE: Sly3 resource transition; original input and produced-object contracts pending.
// SLY3_CFLAGS: -Os -G0
#include "resource_attachment_api.h"
typedef int qword __attribute__((mode(TI)));
struct MATRIX4 {
    qword rows[4];
};
struct VirtualEntry {
    short delta, padding;
    void *function;
};
struct Subject {
    char opaque0[0xC];
    struct VirtualEntry *table;
};
struct Parameter {
    char opaque0[0x90];
    void *channel90;
    char opaque94[0xB0 - 0x94];
    unsigned char payloadB0[1];
};
struct Command0 {
    char opaque0[0xC];
    struct VirtualEntry *table;
    char opaque10[0x30 - 0x10];
    struct Subject *subject30;
    void *parameter34;
};
struct Command1 {
    char opaque0[0xC];
    struct VirtualEntry *table;
    char opaque10[0x38 - 0x10];
    struct Subject *subject38;
    int mode3C;
};
struct Transition {
    char opaque0[0x10];
    char *owner10;
    int word14;
    char cleanup18[0x18];
    struct Subject *subject30;
    int state34;
    float time38;
    struct Parameter *parameter3C;
};
struct Clock {
    float time, step;
};
extern struct Clock D_0036BB98;
extern qword D_00317560;
void func_00238AE8(void *);
void func_00238AB8(struct Transition *);
void func_001A4CD0(void *receiver, int state) {
    struct Transition *transition = receiver;
    if (state == transition->state34) return;
    if (transition->state34 == 0) {
        func_0013BD88(transition->subject30, (int)transition->owner10);
        transition->subject30 = 0;
        func_002568E8(transition->owner10, 0, 0, D_00317560);
    }
    func_00238AE8(transition->cleanup18);
    transition->state34 = state;
    transition->time38 = D_0036BB98.time;
    switch (state) {
        case 0: {
            struct Command0 *command;
            struct VirtualEntry *entry;
            func_0013BD00(transition->subject30, (int)transition->owner10);
            command = func_00238690(transition->owner10 + 0x29C, 0xCC);
            command->subject30 = transition->subject30;
            command->parameter34 = transition->parameter3C->payloadB0;
            entry = &command->table[8];
            ((void (*)(void *))entry->function)((char *)command + entry->delta);
            if (transition->parameter3C->channel90) {
                struct MATRIX4 matrix;
                struct Subject *subject = transition->subject30;
                struct VirtualEntry *query = &subject->table[37];
                void *result = ((void *(*)(void *, struct MATRIX4 *))query->function)((char *)subject + query->delta, &matrix);
                func_002568E8(transition->owner10, transition->parameter3C, result, matrix.rows[3]);
            }
            break;
        }
        case 1: {
            struct Command1 *command = func_00238690(transition->owner10 + 0x29C, 0xC9);
            struct VirtualEntry *entry;
            command->mode3C = 4;
            command->subject38 = transition->subject30;
            entry = &command->table[8];
            ((void (*)(void *))entry->function)((char *)command + entry->delta);
            break;
        }
        case -1: func_00238AB8(transition);
        break;
    }
}
