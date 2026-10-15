// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct VTable { unsigned char pad[0x48]; short adjust, unused; void (*callback)(void *); } VTable;
typedef struct Object { unsigned char pad[0xC]; VTable *vtable; } Object;
typedef struct Node { unsigned char pad[0xF0]; Object *object; } Node;
typedef struct State { unsigned char pad[0x30]; int count; Node *nodes[0]; } State;
// Notify every non-null object associated with the current node array.
void func_0024BD80(State *state)
{
    int index;
    for (index = 0; index < state->count; index++) {
        Object *object = state->nodes[index]->object;
        if (object) {
            VTable *vtable = object->vtable;
            vtable->callback((char *)object + vtable->adjust);
        }
    }
}
