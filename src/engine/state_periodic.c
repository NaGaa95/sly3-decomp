// SLY3_CFLAGS: -Os -G0
#include "attachment_creation_api.h"

struct MatrixPrefix { AttachmentPackedPosition rows[4]; };
struct MatrixEntry {
    short adjustment, reserved;
    struct MatrixPrefix *(*method)(void *);
};
struct PeriodicOwnerPrefix {
    unsigned char opaque00[0xC];
    struct MatrixEntry *table;
    unsigned char opaque10[0x218 - 0x10];
    int pending;
};
struct PeriodicStatePrefix {
    unsigned char opaque00[0x10];
    struct PeriodicOwnerPrefix *owner;
    unsigned char opaque14[0x30 - 0x14];
    int mode;
    unsigned char opaque34[4];
    float lastEmission;
};
struct PeriodicClockPrefix { float time; };
struct AttachmentResultPrefix {
    unsigned char opaque00[0x54];
    int mode;
};
struct PeriodicGamePrefix {
    unsigned char opaque00[0x47A8];
    void *attachmentSpace;
};
extern struct PeriodicClockPrefix D_0036BB98;
extern struct PeriodicGamePrefix D_00475480;
void func_002389A0(void *unused_receiver);
void func_0016D840(void *state, int mode);

void func_0016D760(void *receiver)
{
    struct PeriodicStatePrefix *state = receiver;
    int previous;
    func_002389A0(state);
    do {
        previous = state->mode;
        if (previous < 4) {
            if (previous >= 2 && state->owner->pending)
                func_0016D840(state, -1);
        }
    } while (previous != state->mode);
    if (previous == 1 || previous == 4) {
        if (D_0036BB98.time - state->lastEmission > 1.0f) {
            struct PeriodicGamePrefix *game = &D_00475480;
            struct MatrixEntry *entry;
            struct MatrixPrefix *matrix;
            struct AttachmentResultPrefix *result;
            state->lastEmission = D_0036BB98.time;
            entry = state->owner->table + 36;
            matrix = entry->method((char *)state->owner + entry->adjustment);
            result = func_001738C0(game->attachmentSpace,
                                   matrix->rows[3], (int)state->owner);
            result->mode = 3;
        }
    }
}
