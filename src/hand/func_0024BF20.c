// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct Parent { unsigned char pad[0x44]; int mode; } Parent;
typedef struct Object { unsigned char pad[0xDC]; Parent *parent; unsigned char gap[8]; int id; } Object;
typedef struct State { unsigned char pad[0x30]; int count; Object *objects[16]; unsigned int output_count; Object *output[5]; } State;
// Retain up to five valid objects with no parent or an eligible parent mode.
void func_0024BF20(State *state)
{
    int index;
    state->output_count = 0;
    for (index = 0; index < state->count; index++) {
        Object *object = state->objects[index];
        Parent *parent;
        if (object->id != -1 && ((parent = object->parent) == 0 || parent->mode == 1 || parent->mode == 2)) {
            unsigned int count = state->output_count;
            if (count < 5) {
                state->output[count] = object;
                state->output_count = count + 1;
            }
        }
    }
}
