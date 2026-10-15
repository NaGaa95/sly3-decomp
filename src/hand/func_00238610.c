// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct VTable { unsigned char pad[0x70]; short adjust, unused; int (*callback)(void *, int, int); } VTable;
typedef struct Object { unsigned char pad[0xC]; VTable *vtable; } Object;
typedef struct State { int unused, count; Object *objects[0]; } State;
// Traverse backwards until an object handles both original arguments.
void func_00238610(State *state, int first, int second)
{
    int index;
    for (index = state->count - 1; index >= 0; index--) {
        Object *object = state->objects[index];
        VTable *vtable = object->vtable;
        if (vtable->callback((char *)object + vtable->adjust, first, second))
            break;
    }
}
