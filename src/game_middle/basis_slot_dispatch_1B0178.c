// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int StateVector __attribute__((mode(TI)));
struct Method { short adjustment, word2; void *function; };
struct SlotTable {
    unsigned char prefix0[0x120];
    struct Method position;
    unsigned char prefix1[0x2E8 - 0x128];
    struct Method dispatch;
};
struct PositionRecord {
    unsigned char prefix[0x30];
    StateVector value;
};
struct SlotActor {
    unsigned char prefix[0xC];
    struct SlotTable *methods;
    unsigned char gap10[0x19E0 - 0x10];
    int state;
    unsigned char gap19E4[0x19F4 - 0x19E4];
    void *argument;
};
extern StateVector D_00317550;
void func_00153498(char *actor);
StateVector func_001AFE60(void *actor);
void func_001B0178(struct SlotActor *actor)
{
    func_00153498((char *)actor);
    if (actor->state == 0x11) {
        struct Method *dispatch = &actor->methods->dispatch;
        void *self = (char *)actor + dispatch->adjustment;
        StateVector basis = func_001AFE60(actor);
        struct Method *position = &actor->methods->position;
        StateVector axis = D_00317550;
        struct PositionRecord *record = ((struct PositionRecord *(*)(void *))position->function)((char *)actor + position->adjustment);
        ((void (*)(void *, int, void *, StateVector, StateVector, StateVector))dispatch->function)(self, 7, actor->argument, basis, axis, record->value);
    }
}
