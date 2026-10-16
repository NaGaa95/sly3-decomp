// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct TaskCleanupOwner {
    unsigned char opaque00[0x164];
    unsigned int saved;
    unsigned char opaque168[0x50];
    int active;
};
struct TaskCleanupState {
    unsigned char opaque00[0x10];
    TaskCleanupOwner *owner;
    unsigned char opaque14[0x28];
    unsigned int saved;
};
extern "C" {
extern char D_0036C700[];
void func_00238980(void *receiver);
void func_001F6148(void *receiver, int state, void *context);
void func_001F5CC8(char *receiver);
void func_001854C8(void *context, int event, void *owner);
void func_00252FC0(void *owner, int bit);
}
extern "C" void func_001F5B88(void *receiver)
{
    TaskCleanupState *state = static_cast<TaskCleanupState *>(receiver);
    func_00238980(state);
    func_001F6148(state, -1, 0);
    func_001F5CC8(reinterpret_cast<char *>(state));
    state->owner->saved = state->saved;
    func_001854C8(D_0036C700, 0x1B, state->owner);
    func_00252FC0(state->owner, 0x41);
    state->owner->active = 0;
}
