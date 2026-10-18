// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "vector_intrinsics.h"
struct VEntry { short delta, pad; void *function; };
struct Input { float x, y, amount; int word0C, word10; };
struct Actor {
    unsigned char prefix00[0xC];
    struct VEntry *vtable;
    unsigned char gap10[0x134 - 0x10];
    struct Input *input;
    unsigned char gap138[0x1F0 - 0x138];
    int active;
    unsigned char gap1F4[0x204 - 0x1F4];
    float heading;
    int leftHeld;
    int rightHeld;
};
struct World { unsigned char prefix[0x1C64]; void *pending; };
extern "C" {
extern struct World *D_0038AE90;
extern int D_00348040[3][3];
char *func_001F4A80(void *self);
float func_002A3EE8(float y, float x);
float func_00168108(void *controller, float x, float y, float value);
float func_0011E3B8(float angle);
unsigned int func_001A7A80(void *receiver, unsigned int mask, float threshold);
qword func_0023D888(struct Actor *self);
void func_001E4900(void *owner, int mode);
}
extern "C" void func_0020FC58(struct Actor *self)
{
    char *controller;
    float *direction;
    float desired, value, turn;
    int side, row, action;
    struct VEntry *entry;
    self->input->word0C = 0;
    self->input->word10 = 0;
    controller = func_001F4A80(self);
    entry = &self->vtable[36];
    direction = ((float *(*)(void *))entry->function)((char *)self + entry->delta);
    desired = func_002A3EE8(direction[1], direction[0]);
    if (controller && 0.5f < self->input->amount)
        value = func_00168108(controller, self->input->x, self->input->y, desired);
    else
        value = desired;
    if (D_0038AE90->pending)
        self->heading = value;
    if (!self->active)
        return;
    turn = func_0011E3B8(value - desired);
    if (0.15f < turn)
        side = 1;
    else if (turn < -0.15f)
        side = 2;
    else
        side = 0;
    if (func_001A7A80(self->input, 0x40, 0.15f)) {
        self->leftHeld = 1;
        row = 1;
    } else if (func_001A7A80(self->input, 0x80, 0.15f)) {
        self->rightHeld = 1;
        row = 2;
    } else {
        qword point = func_0023D888(self);
        if (!side) {
            row = 0;
        } else {
            float lane = PackedVectorX(point);
            if (150.0f < lane)
                row = 1;
            else if (lane < -150.0f)
                row = 2;
            else
                row = 0;
        }
    }
    action = D_00348040[row][side];
    if (action) {
        func_001E4900(D_0038AE90, 0);
        func_001E4900(D_0038AE90, action);
    }
}
