// SLY3_CFLAGS: -Os -G0
typedef unsigned int CommandPosition __attribute__((mode(TI)));
struct ActorMethod { short adjustment, word2; void *function; };
struct ActorTable {
    unsigned char prefix[0x110];
    struct ActorMethod setPosition;
    struct ActorMethod setBasis;
    struct ActorMethod direction;
};
struct CommandActor { unsigned char prefix[0xC]; struct ActorTable *methods; unsigned char gap10[0x1C0 - 0x10]; unsigned char basis[1]; };
struct CommandTarget { unsigned char prefix[0xC]; struct ActorTable *methods; };
struct CommandState { struct CommandActor *actor; void *saved; };
extern void *D_00479A64;
CommandPosition func_001C03A0(void *actor, void *parameters, float duration);
void *func_001F4A80(void *actor);
float func_002A3EE8(float y, float x);
void func_0024E878(void *actor, float heading);
void func_00166548(void *target);
void func_0017D840(void *table, void *actor);

void func_001C11E0(struct CommandState *state, void *parameters)
{
    CommandPosition position = func_001C03A0(state->actor, parameters, 0.0f);
    struct CommandActor *actor = state->actor;
    void *saved = state->saved;
    struct ActorMethod *method = &actor->methods->setPosition;
    ((void (*)(void *, CommandPosition))method->function)((char *)actor + method->adjustment, position);
    state->saved = saved;
    {
        struct CommandTarget *target = func_001F4A80(state->actor);
        if (target) {
            struct ActorMethod *query = &target->methods->direction;
            float *direction = ((float *(*)(void *))query->function)((char *)target + query->adjustment);
            func_0024E878(state->actor, func_002A3EE8(direction[1], direction[0]));
            {
                struct CommandActor *current = state->actor;
                struct ActorMethod *apply = &current->methods->setBasis;
                ((void (*)(void *, void *))apply->function)((char *)current + apply->adjustment, (char *)current + 0x1C0);
            }
            func_00166548(target);
        }
    }
    func_0017D840(D_00479A64, state->actor);
}
