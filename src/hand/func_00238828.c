// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct VTable { unsigned char pad[0x68]; short adjust; short unused; int (*callback)(void *); } VTable;
typedef struct Object { unsigned char pad[0xC]; VTable *vtable; } Object;
typedef struct State { int unused, count; Object *objects[0]; } State;
// Visit objects in reverse order until a virtual callback succeeds.
void func_00238828(State *state)
{
    int index;
    for (index = state->count - 1; index >= 0; index--) {
        Object *object = state->objects[index];
        VTable *vtable = object->vtable;
        if (vtable->callback((char *)object + vtable->adjust))
            break;
    }
}
