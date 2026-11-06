// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// func_0021B4F8, func_0021B7E8 and func_0021BC58 share one translation unit and therefore one .rodata block (0x325E30..0x325EC8):
// jump table of func_0021B4F8, the ease curve and jump table of func_0021B7E8, the tables of func_0021BC58, the curve D_00325EA8
// (read by other units) and finally the two file-scope sound id tables.
#include "approach_curve.h"
extern "C" {
#include "matrix_xy_resource_api.h"
}
struct Method { short delta, reserved; void (*call)(void *); };
// A pair of ramped values (current[i] follows target[i]) driven by a mode; modes -1..6, the update function below picks the next mode.
struct Controller {
    unsigned char opaque00[0xC];
    Method *methods;
    unsigned char opaque10[0x48 - 0x10];
    int state;
    unsigned char opaque4C[0x120 - 0x4C];
    float current[2];
    float target[2];
    unsigned char opaque130[8];
    int mode;
    unsigned char opaque13C[4];
    int slot;
    int previous;
};
extern "C" {
void func_0021B6C0(Controller *self);
void func_00262280(Controller *self, int id);
void func_00262450(Controller *self, int id);
void func_00261580(Controller *self, int id, float value);
void func_00262B60(Controller *self, int id, int *slot);
int func_00260758(Controller *self, int id);
extern float D_0036BB9C;
// kRiseIds and kFallIds below are the objects at D_00325EB8 and D_00325EC0. func_0021B7E8 reads them through these D_ addresses:
// the assembler pairs a %hi that the compiler repeats in a loop's branch delay slot with the next %lo of the same symbol, which
// would otherwise be a %lo of the other function and could not be bound to the function that owns the %hi.
extern const int D_00325EB8[2];
extern const int D_00325EC0[2];
}
static const int kRiseIds[2] = { 0x792, 0x793 };
static const int kFallIds[2] = { 0x795, 0x796 };
// Switch to a new mode: leaving mode 2 stops its sounds, mode 1 restarts them at the target values, mode 2 starts the fall sounds
// of the values that are above their target, modes 5 and 6 select a slot sound.
extern "C" void func_0021B4F8(Controller *self, int mode)
{
    int id;
    if (self->mode == mode) return;
    switch (self->mode) {
    case -1:
        self->previous = self->mode;
        break;
    case 2:
        for (int i = 0; i < 2; i++) func_00262280(self, kFallIds[i]);
        break;
    }
    self->mode = mode;
    id = -1;
    switch (mode) {
    case -1:
        self->methods[54].call((char *)self + self->methods[54].delta);
        break;
    case 1:
        func_0021B6C0(self);
        for (int i = 0; i < 2; i++) {
            int sound = kRiseIds[i];
            self->current[i] = self->target[i];
            func_00262450(self, sound);
            func_00261580(self, sound, self->current[i]);
        }
        break;
    case 2:
        for (int i = 0; i < 2; i++) {
            int sound = kFallIds[i];
            if (self->current[i] > self->target[i]) func_00262450(self, sound);
        }
        break;
    case 5:
        id = 0x3C5;
        break;
    case 6:
        id = 0x3C6;
        break;
    }
    func_00262B60(self, id, &self->slot);
}
// Per-frame update: choose the mode from the current and target values (zero target: off, target below current: mode 2, above:
// mode 3, equal: mode 1) and ease the values towards the targets in mode 3; repeat while the mode keeps changing.
extern "C" void func_0021B7E8(Controller *self)
{
    int mode;
    do {
        mode = self->mode;
        switch (mode) {
        case -1:
            break;
        case 0:
            if (self->state == 2 || self->state == 3) func_0021B4F8(self, 1);
            break;
        case 1:
        case 5:
        case 6:
            if (self->target[0] <= 0.0f || self->target[1] <= 0.0f) func_0021B4F8(self, -1);
            else if (self->target[0] < self->current[0] || self->target[1] < self->current[1]) func_0021B4F8(self, 2);
            else if (self->current[0] < self->target[0] || self->current[1] < self->target[1]) func_0021B4F8(self, 3);
            else func_0021B4F8(self, 1);
            break;
        case 2: {
            int busy = 0;
            for (int i = 0; i < 2; i++) busy |= func_00260758(self, D_00325EC0[i]);
            if (!busy) func_0021B4F8(self, 3);
            break;
        }
        case 3: {
            int settled = 1;
            for (int i = 0; i < 2; i++) {
                static const ApproachCurve ease = { 100.0f, 0.0f, 0.5f };
                if (self->current[i] < self->target[i]) self->current[i] = self->target[i];
                else self->current[i] = func_0011E598(self->current[i], self->target[i], &ease, 0, D_0036BB9C);
                func_00261580(self, D_00325EB8[i], self->current[i]);
                if (self->current[i] != self->target[i]) settled = 0;
            }
            if (settled) func_0021B4F8(self, 1);
            break;
        }
        case 4:
            break;
        }
    } while (self->mode != mode);
}
struct Panel {
    unsigned char prefix[0x94];
    int state;
    unsigned char gap98[0x98];
    int enabled;
    int index;
};
struct Offset { float x, y, z, w; };
extern "C" void *func_00292034(void *destination, int value, int bytes);
// Apply the panel's placement matrix (identity plus the per-index offset) and advance its state to 8 or 9.
extern "C" void func_0021BC58(Panel *object)
{
    static const Offset offsets[2] = { { 470.0f, 136.0f }, { -6.0f, 373.0f } };
    static const int states[2] = { 8, 9 };
    MatrixXYValue matrix;
    if ((unsigned int)(object->state - 8) < 2) {
        if (!object->enabled || object->index == -1) {
            func_00292034(&matrix, 0, sizeof(matrix));
            matrix.value[3] = 1.0f;
            matrix.value[0] = 1.0f;
        } else {
            func_00292034(&matrix, 0, sizeof(matrix));
            {
                const Offset *pair = &offsets[object->index];
                matrix.value[0] = 1.0f;
                matrix.value[3] = 1.0f;
                matrix.value[4] = pair->x;
                matrix.value[5] = pair->y;
            }
        }
        if (object->index == -1)
            object->state = 8;
        else
            object->state = states[object->index];
        func_00262848(object, &matrix);
    }
}
// Read by func_00216318 and func_00217040 of other units.
extern const ApproachCurve D_00325EA8;
const ApproachCurve D_00325EA8 = { 2000.0f, 500.0f, 1.5f };
