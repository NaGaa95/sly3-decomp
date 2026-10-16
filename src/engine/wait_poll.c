// SLY3_CFLAGS: -Os -G0
typedef struct WaitClock { float time; } WaitClock;
extern WaitClock D_0036BB98;
typedef struct WaitDescriptor { int kind; int word4; float duration; } WaitDescriptor;
typedef struct WaitOwner { char prefix[0x10F0]; int phase; } WaitOwner;
typedef struct WaitState {
    char prefix[0x10];
    WaitOwner *owner;
    int word14;
    void *handle;
    char unaccessed[0x38-0x1C];
    WaitDescriptor *descriptor;
    float started;
    int active;
} WaitState;
int func_001D96B8(void *handle);
int func_001DA768(void *handle);
int func_001DA400(void *handle);
int func_001D7F90(void *handle);
int func_00238AD0(void *state);
void func_00238AE8(void *handleSlot);
void func_00198490(void *state);

int func_00197A60(WaitState *state)
{
    if (!state->active)
        return 0;
    switch (state->descriptor->kind) {
    case 6:
        switch (state->owner->phase) {
        case -1:
            if (func_001D96B8(state->handle)) state->active=0;
            break;
        case 0:
            if (func_001DA768(state->handle)) state->active=0;
            break;
        case 1:
            if (func_001DA400(state->handle)) state->active=0;
            break;
        }
        break;
    case 7:
        if (func_001D7F90(state->handle)) state->active=0;
        break;
    case 5:
        if (state->descriptor->duration<D_0036BB98.time-state->started)
            state->active=0;
        break;
    case 13: case 14: case 17: case 18:
        if (func_00238AD0(state)) state->active=0;
        break;
    }
    if (!state->active) {
        func_00238AE8(&state->handle);
        func_00198490(state);
    }
    return state->active;
}
