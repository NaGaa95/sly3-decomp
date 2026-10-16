// SLY3_CFLAGS: -Os -G0
typedef int ControlUpdateQword __attribute__((mode(TI)));
struct ControlUpdateState {
    char prefix[0x10];
    void *owner;
    char unaccessed14[0x30-0x14];
    int mode;
    char unaccessed34[0x50-0x34];
    ControlUpdateQword basis[3];
    int enabled;
    char unaccessed84[0xD0-0x84];
    int phase;
};
void func_001317B0(void *state);
void func_00132A50(void *state);
void func_00133388(void *state);
void func_00132438(void *state);
void func_0024E988(void *owner, void *basis);

void func_001323C8(struct ControlUpdateState *state)
{
    func_001317B0(state);
    func_00132A50(state);
    func_00133388(state);
    func_00132438(state);
    if (state->enabled && !state->mode && state->phase >= 2)
        func_0024E988(state->owner, state->basis);
}
