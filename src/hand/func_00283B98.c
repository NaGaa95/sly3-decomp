// SLY3_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original bounded record insertion, with verified field sizes.
#include "m2c_prelude.h"

typedef struct Entity { u8 reserved[0x18]; s32 identifier; } Entity;
typedef struct State { u8 reserved[0x10]; s32 identifier; Entity *entity; } State;
void func_00283B98(State *state, Entity *entity) {
    s32 identifier = -1;
    if (entity != NULL) identifier = entity->identifier;
    state->entity = entity;
    state->identifier = identifier;
}
